#include "stdafx.h"
#include "FieldLogic.h"
#include "RecordDAO.h"
#include "FieldDAO.h"
#include "SystemLogic.h"

CFieldLogic::CFieldLogic(CString dbName,CString tableName)
{
	this->tdfPath = DEFAULT_ROOT+CString("/")+dbName+CString("/")+tableName+CString(".tdf");
	this->trdPath = DEFAULT_ROOT+CString("/")+dbName+CString("/")+tableName+CString(".trd");
	this->dbName = dbName;
	this->tbName = tableName;
}


CFieldLogic::~CFieldLogic(void)
{
}

//´´½¨×Ö¶Î
int CFieldLogic::CreateField(CFieldEntity &field)
{
	vector<CFieldEntity> flist=CFieldDAO::ReadFieldList(tdfPath);
	bool fExist=false;
	for (vector<CFieldEntity>::iterator ite=flist.begin();ite!=flist.end();++ite)
	{
		if(ite->GetName()==field.GetName())
		{
			fExist=true;
			break;
		}
	}

	if(!fExist)
	{
		int counter = CFieldDAO::GetFieldCounter(tdfPath);
		field.SetId(++counter);
		if(!CFieldDAO::WriteAnField(field,tdfPath))
			return ADD_ERROR;
		
		if(!CFieldDAO::SaveFieldCounter(tdfPath,counter))
			return SAVE_COUNTER_ERROR;

		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("created field: ")+field.GetName()+CString(". database: ")+dbName+CString(" table: ")+tbName);

		return YES;
	}
	else
	{
		return FIELD_EXIST;
	}
}

//É¾³ý×Ö¶Î
int CFieldLogic::DeleteField(CString &fieldName)
{
	vector<CFieldEntity> list = CFieldDAO::ReadFieldList(tdfPath);
	int index = 0;

	for (int i = 0; i < list.size(); i++)
	{
		if(list[i].GetName()==fieldName)
		{
			index = i;
			break;
		}
	}

	if(!CRecordDAO::DeleteFieldRecord(trdPath,index+1))
		return DELETE_ERROR;
	if (!CFieldDAO::DeleteField(fieldName, tdfPath))
		return DELETE_ERROR;
	CSystemLogic sysLogic;
	sysLogic.WriteLog(CString("deleted field: ")+fieldName+CString(". database: ")+dbName+CString(" table: ")+tbName);
	return YES;
}

//ÐÞ¸Ä×Ö¶Î
int CFieldLogic::ModifyField(CFieldEntity &field)
{
	if(CFieldDAO::ModifyField(field,tdfPath))
	{
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("modified field, field id:")+CUtil::IntegerToString(field.GetId())
						+CString(" database: ")+dbName+CString(" table: ")+tbName);
	
		return YES;
	}
	else
		return MODIFY_ERROR;
}


vector<CFieldEntity> CFieldLogic::GetFieldList()
{
	return CFieldDAO::ReadFieldList(this->tdfPath);
}
