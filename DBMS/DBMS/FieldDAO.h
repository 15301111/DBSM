#pragma once
#include "Global.h"
#include "FieldEntity.h"

class CFieldDAO
{
public:
	CFieldDAO(void);
	~CFieldDAO(void);

	static vector<CFieldEntity> ReadFieldList(CString &tbFileName);//���ļ���ȡ�ֶ��б�
	static bool WriteAnField(CFieldEntity &newField,CString &tdfFileName);//�ļ�����һ���ֶμ�¼
	static bool DeleteField(CString &fieldName,CString &tdfFileName);//���ļ�ɾ��һ���ֶ���Ϣ
	static bool ModifyField(CFieldEntity &field,CString &tdfFileName);//���޸ĺ���ֶ�д���ļ�
	
	static int GetFieldCounter(CString &fieldFileName);				//��ȡ���ݿ�ļ�����
	static bool SaveFieldCounter(CString &fieldFileName,int counter);//���������
};

