#pragma once
#include "Global.h"
#include "RecordEntity.h"
#include "FieldEntity.h"
#include <algorithm>
using namespace std;

class CIndexLogic{
private:
	CString dbName;
	CString tbName;
	CString pkName;
	CString uniName;
public:
	CIndexLogic(CString dbname, CString tableName);
	~CIndexLogic(void);
	bool sort(CRecordEntity &records);

	

	
	




};
