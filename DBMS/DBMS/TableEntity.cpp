#include "stdafx.h"
#include "TableEntity.h"


CTableEntity::CTableEntity(int id,CString name,CString dbName,int fieldNum,int recordNum):
	m_id(id),m_sName(name),m_sDBName(dbName),m_iFieldNum(fieldNum),m_iRecordNum(recordNum)
{
	m_sCreateTime=CUtil::GetCurrTime();
	m_sModifyTime=m_sCreateTime;
}


CTableEntity::~CTableEntity(void)
{
}
