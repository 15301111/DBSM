#pragma once
#include "Global.h"

class CDBEntity
{

private:
	int m_id;
	CString m_sName;
	int m_iType;
	int m_iTableNum;
	CString m_sCreatTime;

public:
	CDBEntity(int id=INVALID,CString name=L"NewDatabase",int type=DB_USER,int tableNum=0);
	CDBEntity(CString &str);
	~CDBEntity(void);

	int GetId() { return m_id; };
	CString GetName() { return m_sName; };
	int GetType() { return m_iType; };
	int GetTableNum() { return m_iTableNum; };
	CString GetCreateTime() { return m_sCreatTime; };
	CString GetDBPath() { return L"data/"+m_sName+L"/"+m_sName+L".db"; };

	void SetId(int id) { m_id=id; };
	void SetName(CString name) { m_sName=name; };
	void SetType(int type) { m_iType=type; };
	void SetTableNum(int tableNum) { m_iTableNum=tableNum; };
	void SetCreatTime(CString crttime) { m_sCreatTime=crttime; };
};

