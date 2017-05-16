#pragma once
#include <map>
#include "Global.h"
using namespace std;

class CRecordEntity
{
private:
	int m_id;
	map<CString,CString> m_mValues;
public:
	CRecordEntity(int id=INVALID);
	~CRecordEntity(void);

	int GetId() { return m_id; };
	CString GetValue(CString propety) { return m_mValues[propety]; };
	map<CString,CString> GetValues() { return m_mValues; };
	void SetId(int id) { m_id=id; };
	void SetValue(CString propety,CString value) { m_mValues[propety]=value; };
	//void AddAnRecord(CString propety,CString value) { m_mValues.insert(pair<CString,CString>(propety,value)); };
};
