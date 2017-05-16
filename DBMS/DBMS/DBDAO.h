#pragma once
#include "Global.h"
#include "DBEntity.h"


class CDBDAO
{

public:
	CDBDAO(void);
	~CDBDAO(void);

	static vector<CDBEntity> ReadDBList(CString &sysFileName);	//从文件读取数据库列表
	static int ReadDBCounter(CString &sysFileName);				//读取数据库的计数器
	static bool SaveDBCounter(int counter);						//保存计数器
	static bool InitDBFile(CString &dbName);					//创建目录，初始化db文件
	static bool WriteAnDB(CDBEntity &newDB,CString &sysFileName);//新增一个数据库到文件
	static bool ModifyDBName(CString &oldName,CString &newName,CString &sysFileName);//把新的数据库名写入数据库
	static bool ModifyDirName(CString &oldName,CString &newName);//修改数据库文件夹名,数据库文件名，并且修改表文件的数据库名
	static bool DeleteDBRecord(CString &sysFileName,CString &dbname);//删除系统文件中数据库的记录
	static bool DeleteDBFile(CString &dbName);		//根据数据库名删除关于该数据库的全部文件

	static bool BackupDB(CString &dbName,CString &destPath);
	static bool ImportDB(CString &sourcePath,CString &destDBName);
};

