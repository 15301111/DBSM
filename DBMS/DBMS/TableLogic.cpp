#include "stdafx.h"
#include "TableLogic.h"
#include "RecordDAO.h"
#include "TableDAO.h"
#include "FieldDAO.h"
#include "DBDAO.h"
#include "SystemLogic.h"


CTableLogic::CTableLogic(CString dbName)
{
	this->dbPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + dbName + CString(".db");
	this->m_sDBName=dbName;
}


CTableLogic::~CTableLogic(void)
{
}

//根据表名建一张新表
int CTableLogic::CreateTable(CString &tableName)
{
	vector<CTableEntity> tlist=CTableDAO::ReadTableList(dbPath);
	bool tExist=false;
	for (vector<CTableEntity>::iterator ite=tlist.begin();ite!=tlist.end();++ite)
	{
		if(ite->GetName()==tableName)
		{
			tExist=true;
			break;
		}
	}
	if(!tExist)
	{	
		int counter=CDBDAO::ReadDBCounter(dbPath);
		CTableEntity table(++counter,tableName,m_sDBName);
		if(CTableDAO::WriteAnTable(table,dbPath)&&
			CTableDAO::InitTBFile(m_sDBName,tableName)&&
			CTableDAO::SaveTableCounter(dbPath,counter))
		{
			CSystemLogic sysLogic;
			sysLogic.WriteLog(CString("created an table:")+tableName+CString(" database: ")+m_sDBName);
			return YES;
		}
		else
			return ADD_ERROR;
	}
	else
	{
		return TABLE_EXIST;
	}
}

//删除表
int CTableLogic::DeleteTable(CString &tableName)
{
	if(!CTableDAO::DeleteTableRecord(m_sDBName,tableName)||!CTableDAO::DeleteTableFile(m_sDBName,tableName))
		return DELETE_ERROR;
	
	else
	{
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("deleted an table:")+tableName+CString(" database: ")+m_sDBName);
		return YES;	
	}
		
	
}

//修改表名
int CTableLogic::ModifyTBName(CString &tableName,CString &newTableName)
{
	vector<CTableEntity> tblist=CTableDAO::ReadTableList(dbPath);
	CTableEntity newTable;
	bool bExist=false;
	for (vector<CTableEntity>::iterator ite=tblist.begin();ite!=tblist.end();++ite)
	{
		if(ite->GetName()==newTableName)
		{
			bExist=true;
		}
		if (ite->GetName() == tableName)
		{
			newTable = *ite;
			newTable.SetName(newTableName);
		}
	}

	if (bExist)
		return DB_EXIST;
	else
	{
		if (!CTableDAO::ModifyTableName(newTable, dbPath) ||
			!CTableDAO::ModifyDirName(tableName, newTableName, m_sDBName))
			return MODIFY_ERROR;
		else
		{
			CSystemLogic sysLogic;
			sysLogic.WriteLog(CString("modified an table:")+tableName+CString("->")+newTableName+CString(" database: ")+m_sDBName);
			return YES;
		}
	
	}
}

//清空表数据
int CTableLogic::ClearTableData(CString &tableName)
{
	vector<CTableEntity> tlist=CTableDAO::ReadTableList(dbPath);
	bool tExist=false;
	for (vector<CTableEntity>::iterator ite=tlist.begin();ite!=tlist.end();++ite)
	{
		if(ite->GetName()==tableName)
		{
			tExist=true;
			break;
		}
	}
	if(tExist)
	{
		//删除指定表的数据信息
		CString trdPath=DEFAULT_ROOT+CString("/")+this->m_sDBName+CString("/")+tableName+CString(".trd");
		if(CRecordDAO::DeleteAllRecord(trdPath))
		{
			CSystemLogic sysLogic;
			sysLogic.WriteLog(CString("deteted all record of table:")+tableName+CString(" database: ")+m_sDBName);
			return YES;
		}
		else
			return NO;
	}
	else
	{
		return TABLE_NOT_EXIST;
	}	
}

//读取指定页的记录数
vector<CRecordEntity> CTableLogic::LookTable(IN int page,IN CString &tableName,OUT vector<CFieldEntity> &fieldList)
{
	CString trdPath=DEFAULT_ROOT+CString("/")+this->m_sDBName+CString("/")+tableName+CString(".trd");
	CString tdfPath=DEFAULT_ROOT+CString("/")+this->m_sDBName+CString("/")+tableName+CString(".tdf");
	fieldList=CFieldDAO::ReadFieldList(tdfPath);
	return CRecordDAO::ReadRecordList(page,DEFAULT_PAGE_RECORDNUM,trdPath,CFieldDAO::ReadFieldList(tdfPath));
}


vector<CRecordEntity> CTableLogic::ConditionQuery(IN map<CString,CString> condition,IN CString &tableName,
		OUT vector<CFieldEntity> &fieldList)
{
	CString trdPath=DEFAULT_ROOT+CString("/")+this->m_sDBName+CString("/")+tableName+CString(".trd");
	CString tdfPath=DEFAULT_ROOT+CString("/")+this->m_sDBName+CString("/")+tableName+CString(".tdf");
	fieldList=CFieldDAO::ReadFieldList(tdfPath);
	return CRecordDAO::ReadListWithCondition(trdPath,condition);
}

vector<CTableEntity> CTableLogic::GetTableList()
{
	return CTableDAO::ReadTableList(this->dbPath);
}
