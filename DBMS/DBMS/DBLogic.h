#pragma once
#include "Global.h"
#include "DBEntity.h"

class CDBLogic
{
private:
	CString sysPath;
public:
	CDBLogic(void);
	~CDBLogic(void);

	int CreateDatabase(CString &dbName); //����һ�����ݿ������������ݿ�
	int ModifyDBName(CString &oldDBName,CString &newDBName);//����һ�����ݿ����������ݿ�id���޸����ݿ�
	int DeleteDatabase(CString &dbname);//ɾ��ָ�������ݿ�
	vector<CDBEntity> GetDatabaseList();	//�õ����ݿ��б�

	bool BackupDatabase(CString &dbName,CString &destPath);
	bool ImportDatabase(CString &path,CString &dbName);

};

