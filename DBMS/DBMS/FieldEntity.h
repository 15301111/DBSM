#pragma once
#include "Global.h"

class CFieldEntity
{
private:
	int m_id;
	CString m_sName;
	int m_iOrder;
	int m_iType;
	int m_iLength;
	double m_dMax;
	double m_dMin;
	CString m_sDefault;
	int m_isPK;
	int m_isNull;
	int m_isUnique;
	CString m_sComment;

public:
	CFieldEntity(int id=INVALID,CString name=L"NewField",int type=DB_INTEGER,int length=DEFAULT_FIELD_LENGTH,
					int isPk=NO,int isNull=YES,int isUnique=NO,CString comment=L"");
	CFieldEntity(CString &str);
	~CFieldEntity(void);

	int GetId() { return m_id; };
	CString GetName() { return m_sName; };
	int GetOrder() { return m_iOrder; };
	int GetType() { return m_iType; };
	int GetLength() { return m_iLength; };
	double GetMax() { return m_dMax; };
	double GetMin() { return m_dMin; };
	CString GetDefault() { return m_sDefault; };
	int GetIsPK() { return m_isPK; };
	int GetIsNull() { return m_isNull; };
	int GetIsUnique() { return m_isUnique; };
	CString GetComment() { return m_sComment; };

	void SetId(int id) { m_id=id; };
	void SetName(CString name) { m_sName=name; };
	void SetOrder(int order) { m_iOrder=order; };
	void SetType(int type) { m_iType=type; };
	void SetLength(int length) { m_iLength=length; };
	void SetMax(double max) { m_dMax=max; };
	void SetMin(double min) { m_dMin=min; };
	void SetDefault(CString dft) { m_sDefault=dft; };
	void SetIsPK(int isPK) { m_isPK=isPK; };
	void SetIsNull(int isNull) { m_isNull=isNull; };
	void SetIsUnique(int isUnique) { m_isUnique=isUnique; };
	void SetComment(CString comment) { m_sComment=comment; };

};

