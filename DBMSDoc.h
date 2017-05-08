// DBMSDoc.h : CDBMSDoc ��Ľӿ�
//

#pragma once

#include "DBEntity.h"	


class CRKDBMSDoc : public CDocument
{
protected:  // �������л�����
	CRKDBMSDoc();
	DECLARE_DYNCREATE(CRKDBMSDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();       // �������ļ�
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CRKDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	CDBEntity m_dbEntity;	
	CString m_strError;		

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
#endif // SHARED_HANDLERS
public:
	CDBEntity GetDBEntity();
	CString GetError();
	void SetError(CString strError);
};
