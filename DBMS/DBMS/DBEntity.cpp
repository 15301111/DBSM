#include "stdafx.h"
#include "DBEntity.h"
#include "Util.h"


CDBEntity::CDBEntity(int id,CString name,int type,int tableNum):
	m_id(id),m_sName(name),m_iType(type),m_iTableNum(tableNum)
{
	m_sCreatTime=CUtil::GetCurrTime();
}


CDBEntity::CDBEntity(CString &str)
{
	vector<CString> strList=CUtil::StrSplit(str,L"#");
	m_id=CUtil::StringToInteger(strList[0]);
	m_sName=strList[1];
	m_iType=CUtil::StringToInteger(strList[2]);
	m_iTableNum=CUtil::StringToInteger(strList[3]);
	m_sCreatTime=strList[4];
}



CDBEntity::~CDBEntity(void)
{
}
