#include "stdafx.h"
#include "RecordLogic.h"
#include "RecordDAO.h"
#include "FieldDAO.h"
#include <cctype>
#include "Global.h"
#include "SystemLogic.h"
#include"indexDAO.h"
#include "indexLogic.h"

CRecordLogic::CRecordLogic(CString dbname,CString tableName)
{
	this->tdfPath=DEFAULT_ROOT+CString("/")+dbname+CString("/")+tableName+CString(".tdf");
	this->trdPath=DEFAULT_ROOT+CString("/")+dbname+CString("/")+tableName+CString(".trd");
	this->dbName = dbname;
	this->tbName = tableName;
}


CRecordLogic::~CRecordLogic(void)
{
}

int CRecordLogic::IntegrityVerify(CString &val,CFieldEntity &field)
{
	//MessageBox(NULL,CUtil::IntegerToString(field.GetType())+" "+val,L"",MB_OK);
	//验证基本的完整性
	switch (field.GetType())
	{
	case DB_INTEGER:
	{
		if (CUtil::OnlyHaveNumber(val))
		{
			int iVal=CUtil::StringToInteger(val);

			if (field.GetMax()!=-1)
			{
				if(iVal>field.GetMax())
					return INTEGRITY_OVER_RANGE;
				
			}

			if (field.GetMin()!=-1)
			{
				if(iVal<field.GetMin())
					return INTEGRITY_OVER_RANGE;
				
			}
		}
		else
		{
			return INTEGRITY_ERROR_TYPE;
		}

		break;
	}
	case DB_BOOL:
	{
		if(val!="true" && val!="false")
			return INTEGRITY_ERROR_TYPE;
		break;
	}
	case DB_VARCHAR:
	{
		Varchar varchars(val);
		if (!CUtil::ValidStr(varchars.GetValue()))
			return INTEGRITY_ERROR_CHAR;

		if (varchars.GetLength()>field.GetLength())
		{
			return INTEGRITY_TOO_LONG;
		}
		break;
	}
	case DB_DATETIME:
	{
		if (val != val.SpanIncluding(L"1234567890-") || val.GetLength()!=10)
			return INTEGRITY_ERROR_TYPE;
		else
		{
			//2014-09-02
			for (int i = 0; i < 10; i++)
			{
				if (i!=4&&i!=7)
				{
					if(val[i]>'9'||val[i]<'0')
						return INTEGRITY_ERROR_DATETYPE;
				}
			}

			if (val[4]!='-'||val[7]!='-')
				return INTEGRITY_ERROR_DATETYPE;
			CString date = val;
			vector<CString> ymd=CUtil::StrSplit(date,CString("-"));
			int m = CUtil::StringToInteger(ymd[1]);
			int d = CUtil::StringToInteger(ymd[2]);
			if(m>12 || (m==2&&d>28))
				return INTEGRITY_ERROR_DATETYPE;
			
			if( ((m==1||m==3||m==5||m==7||m==8||m==10||m==12)&&d>31)||
				((m==2||m==4||m==6||m==9||m==11)&&d>30))
				return INTEGRITY_ERROR_DATETYPE;
		}
		break;
	}
	case DB_DOUBLE:
	{
		if (CUtil::OnlyHaveNumberAndDot(val))
		{
			double iVal=CUtil::StringToDouble(val);
			if (field.GetMax()!=-1)
			{
				if(iVal>field.GetMax()){
					return INTEGRITY_OVER_RANGE;
				}
			}

			if (field.GetMin()!=-1)
			{
				if(iVal<field.GetMin()){
					return INTEGRITY_OVER_RANGE;
				}
			}
		}
		else
			return INTEGRITY_ERROR_TYPE;
		
		break;
	}
	default:
		break;
	}

	//验证主键
	if (field.GetIsPK()==YES)
	{
		if (this->IsNull(val)==YES||this->IsUnique(val,field.GetName())==NO)
		{
			return INTEGRITY_NOT_PK;
		}
	}
	else
	{
		//验证非空
		if (field.GetIsNull()==NO)
		{
			if (this->IsNull(val)==YES)
			{
				return INTEGRITY_NULL_VALUE;
			}
		}
		//验证唯一
		if (field.GetIsUnique()==YES)
		{
			if (this->IsUnique(val,field.GetName())==NO)
			{
				return INTEGRITY_NOT_UNIQUE;
			}
		}
	}
	

	return INTEGRITY_OK;
}


int CRecordLogic::IntegrityVerify(CRecordEntity &record,CFieldEntity &field)
{
	CString val=record.GetValue(field.GetName());
	return this->IntegrityVerify(val,field);
}


int CRecordLogic::IsNull(CString &value)
{
	if (value==CString(""))
	{
		return YES;
	}
	else
	{
		return NO;
	}
}

/***********************************
* 判断是否唯一
************************************/
int CRecordLogic::IsUnique(CString &value,CString &fieldName)
{
	vector<CRecordEntity> list=CRecordDAO::ReadRecordList(trdPath,CFieldDAO::ReadFieldList(this->tdfPath));
	for (vector<CRecordEntity>::iterator ite=list.begin(); ite != list.end(); ++ite)
	{
		if (ite->GetValue(fieldName)==value)
		{
			return NO;
		}
	}
	return YES;
}

//增加记录
extern vector<CRecordEntity> RecordsForIndex;
int CRecordLogic::AddRecord(CRecordEntity &record, vector<CFieldEntity> &fieldList)
{
	//vector<CFieldEntity> flist=CFieldDAO::ReadFieldList(tdfPath);
	//for (vector<CFieldEntity>::iterator ite=flist.begin();ite!=flist.end();++ite)
	//{
	//	int res=CRecordLogic::IntegrityVerify(record,*ite);
	//	if(res!=INTEGRITY_OK)
	//		return res;
	//}
	int count = CRecordDAO::GetRcdCounter(this->trdPath);
	record.SetId(++count);

	if (!CRecordDAO::WriteAnRecord(record, trdPath, fieldList))
		return ADD_ERROR;
	
	if(!CRecordDAO::SaveRcdCounter(this->trdPath,count))
		return SAVE_COUNTER_ERROR;
	
	CIndexLogic cindexlogic(this->dbName,this->tbName);
	cindexlogic.sort(record);

	CSystemLogic sysLogic;
	sysLogic.WriteLog(CString("add an record.")+CString("database: ")+dbName+CString(" table: ")+tbName);

	return YES;
	
}

//删除记录
int CRecordLogic::DeleteRecord(int id)
{
	if (CRecordDAO::DeleteRecord(id, trdPath))
	{
		CString priPath = DEFAULT_ROOT + CString("/") + this->dbName + CString("/") + this->tbName + CString("/") + CString("primary.ind");
		CRecordDAO::DeleteRecord(id, trdPath);
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("deleted an record.")+CString("database: ")+dbName+CString(" table: ")+tbName);
		return YES;
	}
	else
		return DELETE_ERROR;
}


int CRecordLogic::DeleteAllRecord()
{
	if(CRecordDAO::DeleteAllRecord(trdPath))
	{
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("deleted all record.")+CString("database: ")+dbName+CString(" table: ")+tbName);
		return YES;
	}
	else
		return DELETE_ERROR;
}


//修改记录
int CRecordLogic::ModifyRecord(CRecordEntity &record)
{
	if(CRecordDAO::ModifyRecord(record,trdPath,tdfPath)){
		CString priPath = DEFAULT_ROOT + CString("/") + this->dbName + CString("/") + this->tbName + CString("/") + CString("primary.ind");
		CRecordDAO::ModifyRecord(record, priPath, tdfPath);
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("modified record,record id:")+CUtil::IntegerToString(record.GetId())
						+CString("database: ")+dbName+CString(" table: ")+tbName);
		return YES;
	}
	else
		return MODIFY_ERROR;
}


vector<CRecordEntity> CRecordLogic::GetRecordList()
{
	return CRecordDAO::ReadRecordList(trdPath,CFieldDAO::ReadFieldList(this->tdfPath));
}


vector<CRecordEntity> CRecordLogic::ConditionQuery(vector<CFieldEntity> fieldList,
	vector<CString> compare,
	vector<CString> values)
{
	CString pkName = CString("");
	int number = 0;
	for (vector<CFieldEntity>::iterator ite = fieldList.begin();ite != fieldList.end(); ite++) {
		number++;
		if (ite->GetIsPK()) {
			pkName = ite->GetName();
			break;
		}
	}
	vector<CRecordEntity> res;
	if (pkName == CString("") || values[number] == L"") {
		vector<CRecordEntity> rcdList = CRecordDAO::ReadRecordList(trdPath, fieldList);
		for (vector<CRecordEntity>::iterator ite = rcdList.begin();ite != rcdList.end();++ite)
		{
			bool condition = true;
			for (int i = 0; i < compare.size(); i++)
			{
				if (values[i] != L"")
				{
					if (compare[i] == L"="&&ite->GetValue(fieldList[i].GetName()) != values[i])
					{
						condition = false; break;
					}
					else if (compare[i] == L">"&&ite->GetValue(fieldList[i].GetName()) <= values[i])
					{
						condition = false; break;
					}
					else if (compare[i] == L"<"&&ite->GetValue(fieldList[i].GetName()) >= values[i])
					{
						condition = false; break;
					}
				}
			}
			if (condition)
				res.push_back(*ite);
		}
	}
	else {
		CString priPath = DEFAULT_ROOT + CString("/") + this->dbName + CString("/") + this->tbName + CString("/") + CString("primary.ind");
		vector<CRecordEntity> rcdList = CRecordDAO::ReadRecordList(priPath, fieldList);

		bool condition = true;
		if (compare[number] == L"=") {
			int low = 0;
			int high = rcdList.size() - 1;
			while (low < high) {
				int mid = (low + high) / 2;
				if (CUtil::StringToInteger(values[number]) == CUtil::StringToInteger(rcdList[mid].GetValue(pkName)))
					res.push_back(rcdList[mid]);
				else if (CUtil::StringToInteger(values[number]) < CUtil::StringToInteger(rcdList[mid].GetValue(pkName)))
					high = mid - 1;
				else low = mid + 1;
			}
		}
		
	}
	return res;
}

