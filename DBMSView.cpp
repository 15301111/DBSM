

// DBMSView.cpp : CDBMSView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DBMS.h"
#endif

#include "DBMSDoc.h"
#include "DBMSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRKDBMSView

IMPLEMENT_DYNCREATE(CRKDBMSView, CView)

BEGIN_MESSAGE_MAP(CRKDBMSView, CView)
	
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()



CRKDBMSView::CRKDBMSView()
{
	// TODO: �ڴ˴���ӹ������

}

CRKDBMSView::~CRKDBMSView()
{
}

BOOL CRKDBMSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ


	return CView::PreCreateWindow(cs);
}



void CRKDBMSView::OnDraw(CDC* /*pDC*/)
{
	CRKDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

// TODO: �ڴ˴�Ϊ����������ӻ��ƴ��� 
}


// CRKDBMSView ��ӡ

BOOL CRKDBMSView::OnPreparePrinting(CPrintInfo* pInfo)
{

	return DoPreparePrinting(pInfo);
}

void CRKDBMSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CRKDBMSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CDBMSView ���

#ifdef _DEBUG
void CRKDBMSView::AssertValid() const
{
	CView::AssertValid();
}

void CRKDBMSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRKDBMSDoc* CRKDBMSView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRKDBMSDoc)));
	return (CRKDBMSDoc*)m_pDocument;
}
#endif //_DEBUG


// CDBMSView ��Ϣ�������
