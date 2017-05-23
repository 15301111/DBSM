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

	int CreateDatabase(CString &dbName); //接受一个数据库名，创建数据库
	int ModifyDBName(CString &oldDBName,CString &newDBName);//接受一个数据库新名和数据库id，修改数据库
	int DeleteDatabase(CString &dbname);//删除指定的数据库
	vector<CDBEntity> GetDatabaseList();	//得到数据库列表

	bool BackupDatabase(CString &dbName,CString &destPath);
	bool ImportDatabase(CString &path,CString &dbName);

};

