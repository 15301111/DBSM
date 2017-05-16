#include "stdafx.h"
#include "FieldDAO.h"
#include "BinaryFile.h"


CFieldDAO::CFieldDAO(void)
{
}


CFieldDAO::~CFieldDAO(void)
{
}

//从文件读取字段列表
vector<CFieldEntity> CFieldDAO::ReadFieldList(CString &tbFileName)
{
	vector<CFieldEntity> res;
	vector<CString> strList=CBinaryFile::ReadAll(tbFileName);
	if(!strList.empty())
	{
		for (vector<CString>::iterator ite = strList.begin()+1; ite != strList.end(); ++ite)
		{
			vector<CString> tmpList=CUtil::StrSplit(*ite,L"#");
			int id=CUtil::StringToInteger(tmpList[0]);
			CString name=tmpList[1];
			int type=CUtil::StringToInteger(tmpList[3]);
			int length=CUtil::StringToInteger(tmpList[4]);
			int isPK=CUtil::StringToInteger(tmpList[8]);
			int isNull=CUtil::StringToInteger(tmpList[9]);
			int isUnique=CUtil::StringToInteger(tmpList[10]);
			CString comment=tmpList[11];
			CFieldEntity tmpFieldEntity=CFieldEntity(id,name,type,length,isPK,isNull,isUnique,comment);
			tmpFieldEntity.SetMax(CUtil::StringToInteger(tmpList[5]));
			tmpFieldEntity.SetMin(CUtil::StringToInteger(tmpList[6]));
			tmpFieldEntity.SetDefault(tmpList[7]);
			res.push_back(tmpFieldEntity);
		}
	}
	return res;
}

//文件增加一个字段记录
bool CFieldDAO::WriteAnField(CFieldEntity &newField,CString &tdfFileName)
{
	CString str=CUtil::IntegerToString(newField.GetId())+CString("#")+newField.GetName()+CString("#")
		+CUtil::IntegerToString(newField.GetOrder())+CString("#")+CUtil::IntegerToString(newField.GetType())
		+CString("#")+CUtil::IntegerToString(newField.GetLength())+CString("#")+CUtil::IntegerToString(newField.GetMax())
		+CString("#")+CUtil::IntegerToString(newField.GetMin())+CString("#")+newField.GetDefault()+CString("#")
		+CUtil::IntegerToString(newField.GetIsPK())+CString("#")+CUtil::IntegerToString(newField.GetIsNull())
		+CString("#")+CUtil::IntegerToString(newField.GetIsUnique())+CString("#")+newField.GetComment();
	return CBinaryFile::AddAnLine(tdfFileName,str);
}

//从文件删除一条字段信息
bool CFieldDAO::DeleteField(CString &fieldName,CString &tdfFileName)
{
	vector<CString> list = CBinaryFile::ReadAll(tdfFileName);
	if (!list.empty())
	{
		for (vector<CString>::iterator ite=list.begin()+1;ite!=list.end();++ite)
		{
			CFieldEntity temp(*ite);
			if(temp.GetName()==fieldName)
			{
				list.erase(ite);
				break;
			}
		}
		return CBinaryFile::Write(tdfFileName,list);
	}
	else
		return false;
}

//把修改后的字段写入文件
bool CFieldDAO::ModifyField(CFieldEntity &newField,CString &tdfFileName)
{
	vector<CString> list = CBinaryFile::ReadAll(tdfFileName);
	if(list.empty())
		return false;
	else
	{
		for (vector<CString>::iterator ite=list.begin()+1;ite!=list.end();++ite)
		{
			vector<CString> vfield = CUtil::StrSplit(*ite,CString("#"));
			if(vfield[0] == CUtil::IntegerToString(newField.GetId()))
			{
				CString str=CUtil::IntegerToString(newField.GetId())+CString("#")+newField.GetName()+CString("#")
							+CUtil::IntegerToString(newField.GetOrder())+CString("#")+CUtil::IntegerToString(newField.GetType())
							+CString("#")+CUtil::IntegerToString(newField.GetLength())+CString("#")+CUtil::IntegerToString(newField.GetMax())
							+CString("#")+CUtil::IntegerToString(newField.GetMin())+CString("#")+newField.GetDefault()+CString("#")
							+CUtil::IntegerToString(newField.GetIsPK())+CString("#")+CUtil::IntegerToString(newField.GetIsNull())
							+CString("#")+CUtil::IntegerToString(newField.GetIsUnique())+CString("#")+newField.GetComment();
				*ite = str;
				break;
			}
		}
		return CBinaryFile::Write(tdfFileName,list);
	}

	
}


int CFieldDAO::GetFieldCounter(CString &fieldFileName)
{
	CString firstLine=CBinaryFile::ReadFirstLine(fieldFileName);
	CString res = CUtil::StrSplit(firstLine,CString("#"))[0];
	return CUtil::StringToInteger(res);
}


bool CFieldDAO::SaveFieldCounter(CString &fieldFileName,int counter)
{
	return CBinaryFile::SaveCounter(fieldFileName,counter);
}
