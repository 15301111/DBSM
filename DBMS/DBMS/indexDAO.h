#pragma once
#include"FieldEntity.h"
#include"RecordEntity.h"
#include "FieldDAO.h"
class CIndexDAO {
public:
	
	CIndexDAO(void){};
	static bool InitIndFile(CString dbName, CString tableName);              //�����ļ��м���Ӧ���ļ�
	static void writeManyRd(CString dbName, CString tableName, vector<CRecordEntity> records);//�����������ж������м�¼
	static vector<CRecordEntity> readRd(CString dbName, CString tableName);
};

