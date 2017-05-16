#pragma once
#include "Global.h"
#include "TableEntity.h"

class CTableDAO
{
public:
	CTableDAO(void);
	~CTableDAO(void);

	static vector<CTableEntity> ReadTableList(CString &dbFileName);//从文件读取表的列表
	static bool WriteAnTable(CTableEntity &table,CString &dbFileName);//新建一张表到db文件
	static bool InitTBFile(CString &dbName,CString &tbName);	//初始化表描述文件和表的记录文件
	static bool ModifyTableName(CTableEntity &table,CString &dbPath);//把新的表名写入数据库
	static bool ModifyDirName(CString &oldTBName, CString &newTBName,CString &dbName);//修改文件及文件名
	static bool DeleteTableRecord(CString &dbName,CString &tableName);//从数据库中删除表的记录，即清空表
	static bool DeleteTableFile(CString &dbName,CString &tableName);//根据数据库名，找到改目录下的相关表文件
	static bool SaveTableCounter(CString &dbPath,int counter);		//在db文件中保存记录表的id计数器

};

