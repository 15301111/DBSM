#pragma once
#include "Global.h"
#include "FieldEntity.h"

class CFieldDAO
{
public:
	CFieldDAO(void);
	~CFieldDAO(void);

	static vector<CFieldEntity> ReadFieldList(CString &tbFileName);//从文件读取字段列表
	static bool WriteAnField(CFieldEntity &newField,CString &tdfFileName);//文件增加一个字段记录
	static bool DeleteField(CString &fieldName,CString &tdfFileName);//从文件删除一条字段信息
	static bool ModifyField(CFieldEntity &field,CString &tdfFileName);//把修改后的字段写入文件
	
	static int GetFieldCounter(CString &fieldFileName);				//读取数据库的计数器
	static bool SaveFieldCounter(CString &fieldFileName,int counter);//保存计数器
};

