#pragma once
#include "Global.h"

class CTableEntity
{
private:
	int m_id;
	CString m_sName;
	CString m_sDBName;
	int m_iFieldNum;
	int m_iRecordNum;
	CString m_sCreateTime;
	CString m_sModifyTime;

public:
	CTableEntity(int id=INVALID,CString name=L"NewTable",CString dbName=L"",int fieldNum=0,int recordNum=0);
	~CTableEntity(void);

	int GetId() { return m_id; };
	CString GetName() { return m_sName; };
	CString GetDBName() { return m_sDBName; };
	int GetFieldNum() { return m_iFieldNum; };
	int GetRecordNum() { return m_iRecordNum; };
	CString GetFieldPath() { return L"data/"+m_sDBName+L"/"+m_sName+L".tdf"; };
	CString GetRecordPath() { return L"data/"+m_sDBName+L"/"+m_sName+L".trd"; };
	CString GetIntegrityPath() { return L"data/"+m_sDBName+L"/"+m_sName+L".tic"; };
	CString GetIndexPath() { return L"data/"+m_sDBName+L"/"+m_sName+L".tid"; };
	CString GetCreateTime() { return m_sCreateTime; };
	CString GetModifyTime() { return m_sModifyTime; };

	void SetId(int id) { m_id=id; };
	void SetName(CString name) { m_sName=name; };
	void SetDBName(CString dbName) { m_sDBName=dbName; };
	void SetFieldNum(int fieldNum) { m_iFieldNum=fieldNum; };
	void SetRecordNum(int recordNum) { m_iRecordNum=recordNum; };
	void SetCreateTime(CString crtTime) { m_sCreateTime=crtTime; };
	void SetModifyTime(CString modifyTime) { m_sModifyTime=modifyTime; };

};

