#pragma once
#include "Global.h"
#include "TableEntity.h"

class CTableDAO
{
public:
	CTableDAO(void);
	~CTableDAO(void);

	static vector<CTableEntity> ReadTableList(CString &dbFileName);//���ļ���ȡ����б�
	static bool WriteAnTable(CTableEntity &table,CString &dbFileName);//�½�һ�ű�db�ļ�
	static bool InitTBFile(CString &dbName,CString &tbName);	//��ʼ���������ļ��ͱ�ļ�¼�ļ�
	static bool ModifyTableName(CTableEntity &table,CString &dbPath);//���µı���д�����ݿ�
	static bool ModifyDirName(CString &oldTBName, CString &newTBName,CString &dbName);//�޸��ļ����ļ���
	static bool DeleteTableRecord(CString &dbName,CString &tableName);//�����ݿ���ɾ����ļ�¼������ձ�
	static bool DeleteTableFile(CString &dbName,CString &tableName);//�������ݿ������ҵ���Ŀ¼�µ���ر��ļ�
	static bool SaveTableCounter(CString &dbPath,int counter);		//��db�ļ��б����¼���id������

};

