#include "stdafx.h"
#include "RecordDAO.h"
#include "FieldLogic.h"
#include "FieldDAO.h"


CRecordDAO::CRecordDAO(void)
{
}


CRecordDAO::~CRecordDAO(void)
{
}

//从文件新增一条记录,写入文件
bool CRecordDAO::WriteAnRecord(CRecordEntity &record, CString &trdFileName, vector<CFieldEntity> &fieldList)
{
	CString str=CUtil::IntegerToString(record.GetId());
	//map<CString,CString> values = record.GetValues();
	for (vector<CFieldEntity>::iterator ite = fieldList.begin(); ite != fieldList.end(); ++ite)
	{
		str += CString("#") + record.GetValue(ite->GetName());
	}
	//MessageBox(NULL,str,L"",MB_OK);
	return CBinaryFile::AddAnLine(trdFileName,str);
}


//读取指定页的记录数
vector<CRecordEntity> CRecordDAO::ReadRecordList(int page,int pageRcdNum,CString &trdFileName,vector<CFieldEntity> &fieldList)
{
	vector<CRecordEntity> res;
	vector<CString> strList=CBinaryFile::Read(trdFileName,page,pageRcdNum);
	vector<CString>::iterator ite=strList.begin();

	for(;ite!=strList.end();++ite)
	{
		vector<CString> tmpList=CUtil::StrSplit(*ite,L"#");
		CRecordEntity tmpRecord = CRecordEntity(CUtil::StringToInteger(tmpList[0]));
		vector<CFieldEntity>::iterator ite2=fieldList.begin();
		for(int i=1;i<tmpList.size();i++)
		{
			tmpRecord.SetValue(ite2->GetName(),tmpList[i]);
			ite2++;
		}
		res.push_back(tmpRecord);
	}

	return res;
}

//获取全部记录
vector<CRecordEntity> CRecordDAO::ReadRecordList(CString &trdFileName,vector<CFieldEntity> &fieldList)
{
	vector<CRecordEntity> res;
	vector<CString> strList=CBinaryFile::ReadAll(trdFileName);

	if (!strList.empty())
	{
		for (vector<CString>::iterator ite = strList.begin()+1; ite != strList.end(); ++ite)
		{
			vector<CString> tmpList = CUtil::StrSplit(*ite, L"#");
			CRecordEntity tmpRecord = CRecordEntity(CUtil::StringToInteger(tmpList[0]));
			vector<CFieldEntity>::iterator ite2 = fieldList.begin();
			for (int i = 1; i<tmpList.size(); i++)
			{
				tmpRecord.SetValue(ite2->GetName(), tmpList[i]);
				ite2++;
			}
			res.push_back(tmpRecord);
		}
	}

	return res;
}

//按照查询条件读取指定页的记录数？？？？？？？？？？？？？？？？？？？
vector<CRecordEntity> CRecordDAO::ReadListWithCondition(CString &trdFileName,map<CString,CString> condition)
{
	return vector<CRecordEntity>();
}

//从文件修改指定的记录
bool CRecordDAO::ModifyRecord(CRecordEntity &record,CString &trdPath,CString &tdfPath)
{
	vector<CString> list = CBinaryFile::ReadAll(trdPath);
	vector<CFieldEntity> fieldList = CFieldDAO::ReadFieldList(tdfPath);
	if(list.empty())
		return false;
	else
	{
		for (vector<CString>::iterator ite=list.begin()+1;ite!=list.end();++ite)
		{
			vector<CString> temp = CUtil::StrSplit(*ite,L"#");
			if(temp[0] == CUtil::IntegerToString(record.GetId()))
			{
				CString str = CUtil::IntegerToString(record.GetId());
				for (vector<CFieldEntity>::iterator itei = fieldList.begin(); itei != fieldList.end(); ++itei)
				{
					str += CString("#") + record.GetValue(itei->GetName());
				}
				*ite = str;
				break;
			}
		}

		return CBinaryFile::Write(trdPath,list);
	}
	
}

//从文件删除一条记录
bool CRecordDAO::DeleteRecord(int id,CString &trdFileName)
{
	vector<CString> list = CBinaryFile::ReadAll(trdFileName);
	if (list.empty())
		return false;
	else
	{
		for (vector<CString>::iterator ite = list.begin() + 1; ite != list.end(); ++ite)
		{
			vector<CString> temp = CUtil::StrSplit(*ite, L"#");
			if (temp[0] == CUtil::IntegerToString(id))
			{
				list.erase(ite); break;
			}
		}
		return CBinaryFile::Write(trdFileName, list);
	}
}

//从文件删除所有记录
bool CRecordDAO::DeleteAllRecord(CString &trdFileName)
{
	CString firstLine = CBinaryFile::ReadFirstLine(trdFileName);
	vector<CString> list;
	list.push_back(firstLine);
	return CBinaryFile::Write(trdFileName,list);
}

//按照字段名称删除关于该字段的
bool CRecordDAO::DeleteFieldRecord(CString &trdFileName,int index)
{
	vector<CString> list = CBinaryFile::ReadAll(trdFileName);
	CUtil::DeleteFileA(trdFileName);	//删除记录文件
	if (list.empty())
		return false;
	else
	{
		for (vector<CString>::iterator ite=list.begin()+1; ite!=list.end(); ++ite)
		{
			int count = 0;
			CString start, end;
			bool can01 = true, can02 = true;
			for (size_t i = 0; i < ite->GetLength(); i++)
			{
				if (ite->GetAt(i) == '#') ++count;
				if (count == index&&can01)
				{
					can01 = false;
					start = ite->Left(i);
				}

				if (count == index + 1 && can02)
				{
					can02 = false;
					end = ite->Right(ite->GetLength() - i);
				}
			}
			*ite = start + end;
		}
		
		return CBinaryFile::Write(trdFileName,list);
	}
}


int CRecordDAO::GetRcdCounter(CString &trdFileName)
{
	CString firstLine=CBinaryFile::ReadFirstLine(trdFileName);
	CString res = CUtil::StrSplit(firstLine,CString("#"))[0];
	return CUtil::StringToInteger(res);
}


bool CRecordDAO::SaveRcdCounter(CString &trdFileName,int counter)
{
	return CBinaryFile::SaveCounter(trdFileName,counter);
}
