#pragma once
#include "Global.h"
#include "RecordEntity.h"
#include "FieldEntity.h"

class CRecordDAO
{
public:
	CRecordDAO(void);
	~CRecordDAO(void);

	static bool WriteAnRecord(CRecordEntity &record, CString &trdFileName, vector<CFieldEntity> &fieldList);//从文件新增一条记录,写入文件
	static vector<CRecordEntity> ReadRecordList(int page,int pageRcdNum,CString &trdFileName,vector<CFieldEntity> &fieldList);//读取指定页的记录数
	static vector<CRecordEntity> ReadRecordList(CString &trdFileName,vector<CFieldEntity> &fieldList);//获取全部记录
	static vector<CRecordEntity> ReadListWithCondition(CString &trdFileName,map<CString,CString> condition);//按照查询条件读取指定页的记录数
	static bool ModifyRecord(CRecordEntity &record,CString &trdPath,CString &tdfPath);//从文件修改指定的记录
	static bool DeleteRecord(int id,CString &trdFileName);//从文件删除一条记录
	static bool DeleteAllRecord(CString &trdFileName);	//从文件删除所有记录
	static bool DeleteFieldRecord(CString &trdFileName,int index);//按照字段名称删除关于该字段的
	static int GetRcdCounter(CString &trdFileName);//得到计数器
	static bool SaveRcdCounter(CString &trdFileName,int counter);//保存计数器
};

