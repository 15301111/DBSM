#pragma once
#include "Global.h"

class CBinaryFile
{
public:
	CBinaryFile(void);
	~CBinaryFile(void);

	static vector<CString> ReadAll(CString &fileName);	//分条读取全部文件的内容
	static vector<CString> Read(CString &fileName,int pageNo,int pageRcdNo); //读取指定页的文件的内容
	static CString ReadFirstLine(CString &fileName);	//读取第一条文件的内容
	static bool Write(CString &fileName,vector<CString> &str);	//将多条记录一次性写入文件
	static bool AddAnLine(CString &fileName,CString &str);	//在文件末尾加入一条记录
	static bool DeleteRecordByName(CString &fileName,CString &name);
	static bool DeleteRecordById(CString &fileName,int id);
	static bool SaveCounter(CString &filePath,int counter);


};

