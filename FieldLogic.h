#pragma once
#include "Global.h"
#include "FieldEntity.h"

class CFieldLogic
{
private:
	CString tdfPath;
	CString trdPath;
	CString dbName;
	CString tbName;
public:
	CFieldLogic(CString dbName,CString tableName);
	~CFieldLogic(void);

	int CreateField(CFieldEntity &field);
	int DeleteField(CString &fieldName);
	int ModifyField(CFieldEntity &field);
	vector<CFieldEntity> GetFieldList();

};

