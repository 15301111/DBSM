

// DBMSDoc.h : CDBMSDoc ��Ľӿ�
//

#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "DBMS.h"
#endif

#include "DBMSDoc.h"
#include "AppException.h"
#include "DBEntity.h"	
#include "DBLogic.h"	

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRKDBMSDoc

IMPLEMENT_DYNCREATE(CRKDBMSDoc, CDocument)

BEGIN_MESSAGE_MAP(CRKDBMSDoc, CDocument)
END_MESSAGE_MAP()




CRKDBMSDoc::CRKDBMSDoc()
{
	m_strError = _T("");	

}

CRKDBMSDoc::~CRKDBMSDoc()
{
}


BOOL CRKDBMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_dbEntity.SetName(_T("MyDBMS"));	

	CDBLogic dbLogic;
	try
	{
	
		if (dbLogic.GetDatabase(m_dbEntity) == false)
		{
			if (dbLogic.CreateDatabase(m_dbEntity) == false)
			{
				throw new CAppException(_T("Failed to create database��"));
			}

		}

		CString strTitle;
		strTitle.Format(_T("Database(%s)"), m_dbEntity.GetName());
		this->SetTitle(strTitle);
	}
	catch (CAppException* e)	
	{
		m_strError = e->GetErrorMessage();
		delete e;
	}
	
	return TRUE;
}


void CRKDBMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӵ洢����
	}
}

#ifdef SHARED_HANDLERS

//  ����ͼ��֧��
void CRKDBMSDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

#endif // SHARED_HANDLERS



#ifdef _DEBUG
void CRKDBMSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRKDBMSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG




CDBEntity CRKDBMSDoc::GetDBEntity()
{
	return m_dbEntity;
}


CString CRKDBMSDoc::GetError()
{
	//�Ƴ��ո��ַ�
	m_strError.TrimLeft();
	m_strError.TrimRight();

	return m_strError;
}

void CRKDBMSDoc::SetError(CString strError)
{
	m_strError = strError;
}