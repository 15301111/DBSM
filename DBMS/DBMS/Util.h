#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

class CUtil
{
public:
	CUtil(void);
	~CUtil(void);


	static vector<CString> StrSplit(CString str,CString split);//字符串分割函数
	static CString GetCurrTime();							  //得到当前时间
	static CString GetError(int code);						//通过错误码得到错误信息
	static CString GetIcon(int flag);						//根据标志得到是“√”还是“”
	static int IconToInt(CString icon);
	static CString GetDataType(int type);					//得到数据类型代码对应的字面类型
	static int TypeToInt(CString type);
	static CString CharArrToString(char *charArr);			//char*转化成CString
	static char *StringToCharArr(CString cstring);			//CString转化成char*

	static CString IntegerToString(int number);				//int转化成字符串
	static int StringToInteger(CString cstring);			//字符串转化成int

	static int StringToBool(CString cstring);
	static CString BoolToString(int b);

	static double StringToDouble(CString cstring);
	static CString DoubleToString(double doubleNum);

	//static CString VarcharToString(Varchar var);
	//static Varchar StringToVarchar(CString cstring);



	//文件及文件夹操作
	static bool CreateFolder(CString &folderName);			//创建文件夹
	static bool ModifyFolderName(CString &oldname,CString &newname);//修改文件夹名称
	static bool ModifyFileName(CString &oldname,CString &newname);	//修改文件名
	static bool DeleteFolder(CString &folderName);			//删除文件夹
	static bool DeleteFileA(CString &filename);				//删除文件
	static void CopyDirectory(CString source, CString target);//复制文件夹里的内容


	static bool OnlyHaveNumber(CString &str);		//字符串是否只含有数字
	static bool OnlyHaveNumberAndDot(CString &str);	//字符串是否只含有数字和"."
	static bool ValidStr(CString &str);		//字符串是否只含有字母、数字和"_"
};
