#pragma once


class CDBEntity
{
public:
	CDBEntity(void);
	CDBEntity(DatabaseBlock &db);
	CDBEntity(const CString strName);
	~CDBEntity(void);

public:
	DatabaseBlock GetBlock(void);
	void SetBlock(DatabaseBlock db);

	void SetName(CString strName);
	void SetType(bool bType);
	void SetFilepath(CString strFilepath);
	void SetCtTime(SYSTEMTIME tTime);	

	CString GetName(void);
	bool GetType(void);
	CString GetFilepath(void);
	SYSTEMTIME GetCtTime(void);

private:
	CString m_strName;		// 数据库名字
	bool m_bType;			// 数据库种类
	CString m_strFilepath;	// 数据库的文件路径
	SYSTEMTIME m_tCtTime;	// 创建的时间
};