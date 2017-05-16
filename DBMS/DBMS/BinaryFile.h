#pragma once
#include "Global.h"

class CBinaryFile
{
public:
	CBinaryFile(void);
	~CBinaryFile(void);

	static vector<CString> ReadAll(CString &fileName);	//������ȡȫ���ļ�������
	static vector<CString> Read(CString &fileName,int pageNo,int pageRcdNo); //��ȡָ��ҳ���ļ�������
	static CString ReadFirstLine(CString &fileName);	//��ȡ��һ���ļ�������
	static bool Write(CString &fileName,vector<CString> &str);	//��������¼һ����д���ļ�
	static bool AddAnLine(CString &fileName,CString &str);	//���ļ�ĩβ����һ����¼
	static bool DeleteRecordByName(CString &fileName,CString &name);
	static bool DeleteRecordById(CString &fileName,int id);
	static bool SaveCounter(CString &filePath,int counter);


};

