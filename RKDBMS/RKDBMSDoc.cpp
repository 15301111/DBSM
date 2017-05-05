
// RKDBMSDoc.cpp : implementation of the CRKDBMSDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RKDBMS.h"
#endif

#include "RKDBMSDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRKDBMSDoc

IMPLEMENT_DYNCREATE(CRKDBMSDoc, CDocument)

BEGIN_MESSAGE_MAP(CRKDBMSDoc, CDocument)
END_MESSAGE_MAP()


// CRKDBMSDoc construction/destruction

CRKDBMSDoc::CRKDBMSDoc()
{
	// TODO: add one-time construction code here

}

CRKDBMSDoc::~CRKDBMSDoc()
{
}

/***************************************************************
[FunctionName] OnNewDocument
[Function] Create a new document
[Argument] void
[ReturnedValue] BOOL:Whether the operation is successful.TRUE is successful and FALSE is failed.
***************************************************************/
BOOL CRKDBMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Set the document title text
	this->SetTitle(_T("No Database"));
	
	return TRUE;
}




// CRKDBMSDoc serialization

void CRKDBMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRKDBMSDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CRKDBMSDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRKDBMSDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRKDBMSDoc diagnostics

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


// CRKDBMSDoc commands
