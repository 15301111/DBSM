#pragma once
#include "Global.h"
#include "RecordEntity.h"
#include "FieldEntity.h"

class CRecordDAO
{
public:
	CRecordDAO(void);
	~CRecordDAO(void);

	static bool WriteAnRecord(CRecordEntity &record, CString &trdFileName, vector<CFieldEntity> &fieldList);//���ļ�����һ����¼,д���ļ�
	static vector<CRecordEntity> ReadRecordList(int page,int pageRcdNum,CString &trdFileName,vector<CFieldEntity> &fieldList);//��ȡָ��ҳ�ļ�¼��
	static vector<CRecordEntity> ReadRecordList(CString &trdFileName,vector<CFieldEntity> &fieldList);//��ȡȫ����¼
	static vector<CRecordEntity> ReadListWithCondition(CString &trdFileName,map<CString,CString> condition);//���ղ�ѯ������ȡָ��ҳ�ļ�¼��
	static bool ModifyRecord(CRecordEntity &record,CString &trdPath,CString &tdfPath);//���ļ��޸�ָ���ļ�¼
	static bool DeleteRecord(int id,CString &trdFileName);//���ļ�ɾ��һ����¼
	static bool DeleteAllRecord(CString &trdFileName);	//���ļ�ɾ�����м�¼
	static bool DeleteFieldRecord(CString &trdFileName,int index);//�����ֶ�����ɾ�����ڸ��ֶε�
	static int GetRcdCounter(CString &trdFileName);//�õ�������
	static bool SaveRcdCounter(CString &trdFileName,int counter);//���������
};

