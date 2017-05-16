#include "stdafx.h"
#include "TableDAO.h"


CTableDAO::CTableDAO(void)
{
}


CTableDAO::~CTableDAO(void)
{
}


//从文件读取表的列表
vector<CTableEntity> CTableDAO::ReadTableList(CString &dbFileName)
{
	vector<CTableEntity> res;
	vector<CString> strList=CBinaryFile::ReadAll(dbFileName);
	if(!strList.empty())
	{
		vector<CString>::iterator ite=strList.begin();
		vector<CString> firstList=CUtil::StrSplit(*ite,L"#");
		CString dbName=firstList[1];
		++ite;
		for(;ite!=strList.end();++ite)
		{
			vector<CString> tmpList=CUtil::StrSplit(*ite,L"#");
			int id=CUtil::StringToInteger(tmpList[0]);
			CString name=tmpList[1];
			int fieldNum=CUtil::StringToInteger(tmpList[2]);
			int recordNum=CUtil::StringToInteger(tmpList[3]);
			CTableEntity tableEntity=CTableEntity(id,name,dbName,fieldNum,recordNum);
			tableEntity.SetCreateTime(tmpList[4]);
			tableEntity.SetModifyTime(tmpList[5]);
			res.push_back(tableEntity);
		}
	}
	return res;
}

//新建一张表到db文件
bool CTableDAO::WriteAnTable(CTableEntity &table,CString &dbFileName)
{

	//在db文件中新增一条表的描述内容
	CString str=CUtil::IntegerToString(table.GetId())+CString("#")+table.GetName()+CString("#")
		+CUtil::IntegerToString(table.GetFieldNum())+CString("#")+CUtil::IntegerToString(table.GetRecordNum())+CString("#")
		+table.GetCreateTime()+CString("#")+table.GetModifyTime();
	if(CBinaryFile::AddAnLine(dbFileName,str))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//初始化表描述文件和表的记录文件
bool CTableDAO::InitTBFile(CString &dbName,CString &tbName)
{
	CString tdfPath = DEFAULT_ROOT+CString("/")+dbName+CString("/")+tbName+CString(".tdf");
	CString trdPath = DEFAULT_ROOT+CString("/")+dbName+CString("/")+tbName+CString(".trd");
	vector<CString> init;
	init.push_back(CString("0#")+dbName+CString("#")+tbName);
	bool crtTdfFile = CBinaryFile::Write(tdfPath,init);
	bool crtTrdile = CBinaryFile::Write(trdPath,init);
	return crtTdfFile&&crtTrdile;
}

//把新的表名写入数据库
bool CTableDAO::ModifyTableName(CTableEntity &table, CString &dbPath)
{
	vector<CString> list = CBinaryFile::ReadAll(dbPath);
	if (!list.empty())
	{
		for (vector<CString>::iterator ite = list.begin() + 1; ite != list.end(); ++ite)
		{
			vector<CString> tempList = CUtil::StrSplit(*ite, CString("#"));
			if (tempList[0] == CUtil::IntegerToString(table.GetId()))
			{
				CString str = CUtil::IntegerToString(table.GetId()) + CString("#") + table.GetName() + CString("#")
					+ CUtil::IntegerToString(table.GetFieldNum()) + CString("#") + CUtil::IntegerToString(table.GetRecordNum()) + CString("#")
					+ table.GetCreateTime() + CString("#") + table.GetModifyTime();
				*ite = str;
				break;
			}
		}
		return CBinaryFile::Write(dbPath, list);
	}
	else
		return false;
	
}

//从数据库中删除表的记录，即清空表
bool CTableDAO::DeleteTableRecord(CString &dbName,CString &tableName)
{
	CString tbPath=DEFAULT_ROOT+CString("/")+dbName+CString("/")+dbName+CString(".db");
	vector<CString> list = CBinaryFile::ReadAll(tbPath);
	if(list.empty())
		return false;
	else
	{
		vector<CString>::iterator ite=list.begin();
		++ite;
		for (; ite!=list.end(); ++ite)
		{
			vector<CString> temp = CUtil::StrSplit(*ite,CString("#"));
			//如果找到指定的记录
			if (temp[1] == tableName)
			{
				list.erase(ite);
				break;
			}
		}
		if (CBinaryFile::Write(tbPath,list))
			return true;
		else
			return false;
	}

}

//根据数据库名，找到改目录下的相关表文件
bool CTableDAO::DeleteTableFile(CString &dbName,CString &tableName)
{
	CString tdfPath=DEFAULT_ROOT+CString("/")+dbName+CString("/")+tableName+CString(".tdf");
	CString trdPath=DEFAULT_ROOT+CString("/")+dbName+CString("/")+tableName+CString(".trd");
	return CUtil::DeleteFileA(tdfPath)&&CUtil::DeleteFileA(trdPath);
}


bool CTableDAO::SaveTableCounter(CString &dbPath,int counter)
{
	return CBinaryFile::SaveCounter(dbPath,counter);
}


bool CTableDAO::ModifyDirName(CString &oldTBName, CString &newTBName, CString &dbName)
{
	CString tdfPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + oldTBName + CString(".tdf");
	CString tdfNPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + newTBName + CString(".tdf");
	CString trdPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + oldTBName + CString(".trd");
	CString trdNPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + newTBName + CString(".trd");
	if (!CUtil::ModifyFileName(tdfPath, tdfNPath) ||
		!CUtil::ModifyFileName(trdPath, trdNPath))
		return MODIFY_ERROR;
	else
		return YES;
}