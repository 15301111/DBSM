#include "stdafx.h"
#include "FieldEntity.h"


CFieldEntity::CFieldEntity(int id,CString name,int type,int length,int isPK,int isNull,int isUnique,CString comment):
	m_id(id),
	m_sName(name),
	m_iType(type),
	m_iLength(length),
	m_isPK(isPK),
	m_isNull(isNull),
	m_isUnique(isUnique),
	m_sComment(comment)
{
	this->m_iOrder = 0;
	this->m_dMax = INT_MIN;
	this->m_dMin = INT_MAX;
	this->m_sDefault = CString("");

}

CFieldEntity::CFieldEntity(CString &str)
{
	vector<CString> list = CUtil::StrSplit(str,CString("#"));
	m_id = CUtil::StringToInteger(list[0]);
	m_sName = list[1];
	m_iOrder = CUtil::StringToInteger(list[2]);
	m_iType = CUtil::StringToInteger(list[3]);
	m_iLength = CUtil::StringToInteger(list[4]);
	m_dMax = CUtil::StringToDouble(list[5]);
	m_dMin = CUtil::StringToDouble(list[6]);
	m_sDefault = list[7];
	m_isPK = CUtil::StringToInteger(list[8]);
	m_isNull = CUtil::StringToInteger(list[9]);
	m_isUnique = CUtil::StringToInteger(list[10]);
	m_sComment = list[11];

}


CFieldEntity::~CFieldEntity(void)
{
}
