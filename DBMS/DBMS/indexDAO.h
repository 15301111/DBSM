#pragma once
#include"FieldEntity.h"
#include"RecordEntity.h"
#include "FieldDAO.h"
class CIndexDAO {
public:
	
	CIndexDAO(void){};
	static bool InitIndFile(CString dbName, CString tableName);              //创建文件夹及对应的文件
	static void writeManyRd(CString dbName, CString tableName, vector<CRecordEntity> records);//从主键索引中读出所有记录
	static vector<CRecordEntity> readRd(CString dbName, CString tableName);
};

