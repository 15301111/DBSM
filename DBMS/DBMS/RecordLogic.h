#pragma once
#include "Global.h"
#include "RecordEntity.h"
#include "FieldEntity.h"

class CRecordLogic
{
private:
	CString trdPath;
	CString tdfPath;
	CString dbName;
	CString tbName;
public:
	CRecordLogic(CString dbname,CString tableName);
	~CRecordLogic(void);

	int AddRecord(CRecordEntity &record,vector<CFieldEntity> &fieldList);
	int DeleteRecord(int id);
	int DeleteAllRecord();
	int ModifyRecord(CRecordEntity &record);
	vector<CRecordEntity> GetRecordList();
	vector<CRecordEntity> ConditionQuery(vector<CFieldEntity> m_list,
										vector<CString> compare,
										vector<CString> values);

	int IsUnique(CString &value,CString &field);
	int IsNull(CString &value);
	int IntegrityVerify(CRecordEntity &record,CFieldEntity &field);
	int IntegrityVerify(CString &val,CFieldEntity &field);
};

