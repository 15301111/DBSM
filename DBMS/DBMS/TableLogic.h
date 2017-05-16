#pragma once
#include "Global.h"
#include "TableEntity.h"
#include "FieldEntity.h"
#include "RecordEntity.h"

class CTableLogic
{
private:
	CString dbPath;
	CString m_sDBName;

public:
	CTableLogic(CString dbName);
	~CTableLogic(void);

	int CreateTable(CString &tableName); // ���ݱ�����һ���±�
	int DeleteTable(CString &tableName); //ɾ��һ�ű�
	vector<CTableEntity> GetTableList();//�õ����ݿ��ļ��б���б�
	int ModifyTBName(CString &tableName,CString &newTableName);//�޸ı���
	int ClearTableData(CString &tableName);//��ձ�����
	//int RefreshTable(CString &tableName);//ˢ�±�Ľṹ������
	vector<CRecordEntity> ConditionQuery(IN map<CString,CString> condition,IN CString &tableName,
		OUT vector<CFieldEntity> &fieldList);//����ֶ�������ѯ�����condition����ÿ�����Զ�Ӧ��ֵΪ�գ��Ͳ�ѯ��Ӧ�������еļ�¼
	vector<CRecordEntity> LookTable(IN int page,IN CString &tableName,OUT vector<CFieldEntity> &fieldList);//��ȡָ��ҳ�ļ�¼,�Լ���ṹ
};
