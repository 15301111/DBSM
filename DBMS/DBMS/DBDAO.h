#pragma once
#include "Global.h"
#include "DBEntity.h"


class CDBDAO
{

public:
	CDBDAO(void);
	~CDBDAO(void);

	static vector<CDBEntity> ReadDBList(CString &sysFileName);	//���ļ���ȡ���ݿ��б�
	static int ReadDBCounter(CString &sysFileName);				//��ȡ���ݿ�ļ�����
	static bool SaveDBCounter(int counter);						//���������
	static bool InitDBFile(CString &dbName);					//����Ŀ¼����ʼ��db�ļ�
	static bool WriteAnDB(CDBEntity &newDB,CString &sysFileName);//����һ�����ݿ⵽�ļ�
	static bool ModifyDBName(CString &oldName,CString &newName,CString &sysFileName);//���µ����ݿ���д�����ݿ�
	static bool ModifyDirName(CString &oldName,CString &newName);//�޸����ݿ��ļ�����,���ݿ��ļ����������޸ı��ļ������ݿ���
	static bool DeleteDBRecord(CString &sysFileName,CString &dbname);//ɾ��ϵͳ�ļ������ݿ�ļ�¼
	static bool DeleteDBFile(CString &dbName);		//�������ݿ���ɾ�����ڸ����ݿ��ȫ���ļ�

	static bool BackupDB(CString &dbName,CString &destPath);
	static bool ImportDB(CString &sourcePath,CString &destDBName);
};

