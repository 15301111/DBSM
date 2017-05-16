#pragma once

#define STRING_LENGTH 1024	//字符串长度
#define INVALID	0			//主要用于id的不合法的
#define YES 1				//
#define NO 0				//


#define OPERATE_ADD 1		//增加操作
#define OPERATE_MODIFY 2	//修改操作

#define DB_SYSTEM 1			//系统数据库
#define DB_USER 2			//用户数据库

#define DB_INTEGER 1			//整型，对应int
#define DB_BOOL 2				//布尔值类型，对应bool
#define DB_DOUBLE 3				//双精度型，对应double
#define DB_VARCHAR 4			//可变长字符类型，对应CString
#define DB_DATETIME 5			//时间类型，对应SYSTEMTIME

#define DEFAULT_FIELD_LENGTH 20	//默认字段长度
#define DEFAULT_PAGE_RECORDNUM 20 //默认每页显示条目

#define DEFAULT_SYS_FILE CString("data/dbms.sys") //默认的系统文件名称
#define DEFAULT_ROOT CString("data")			//默认数据跟目录

//完整性约束
#define INTEGRITY_OK 300	//正常
#define INTEGRITY_OVER_RANGE 301 //超出范围
#define INTEGRITY_TOO_LONG 302 //字符过长
#define INTEGRITY_ERROR_CHAR 303 //特殊字符
#define INTEGRITY_NULL_VALUE 304//字段空值
#define INTEGRITY_NOT_UNIQUE 305//字段不唯一
#define INTEGRITY_NOT_PK 306//不符合主键约束
#define INTEGRITY_ERROR_TYPE 350//错误类型
#define INTEGRITY_ERROR_DATETYPE 351//错误日期类型

//逻辑层
#define DB_EXIST 307			//数据库已存在
#define DB_NOT_EXIST 308		//数据库不存在
#define FIELD_EXIST 309			//字段已存在
#define FIELD_NOT_EXIST 310		//字段不存在
#define RECORD_NOT_EXIST 311	//记录不存在
#define TABLE_EXIST 312			//表已存在
#define TABLE_NOT_EXIST 313		//表不存在

#define INITIATE_ERROR 314		//初始化错误
#define ADD_ERROR 315			//添加错误
#define MODIFY_ERROR 316		//修改错误
#define DELETE_ERROR 317		//删除错误
#define SAVE_COUNTER_ERROR 318  //保存计数器出错


#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
#include "Util.h"	//工具类
#include "BinaryFile.h"	//文件操作类


class Varchar
{
private:
	CString value;
public:
	Varchar(CString val):value(val){}
	int GetLength() { return value.GetLength(); };
	CString GetValue() { return value; };
};