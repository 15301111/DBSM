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

	int CreateTable(CString &tableName); // 根据表名建一张新表
	int DeleteTable(CString &tableName); //删除一张表
	vector<CTableEntity> GetTableList();//得到数据库文件中表的列表
	int ModifyTBName(CString &tableName,CString &newTableName);//修改表名
	int ClearTableData(CString &tableName);//清空表数据
	//int RefreshTable(CString &tableName);//刷新表的结构和数据
	vector<CRecordEntity> ConditionQuery(IN map<CString,CString> condition,IN CString &tableName,
		OUT vector<CFieldEntity> &fieldList);//多个字段条件查询，如果condition里面每个属性对应的值为空，就查询对应属性所有的记录
	vector<CRecordEntity> LookTable(IN int page,IN CString &tableName,OUT vector<CFieldEntity> &fieldList);//读取指定页的记录,以及表结构
};
