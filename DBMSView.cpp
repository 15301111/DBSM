

// DBMSView.cpp : CDBMSView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// TODO: 在此处添加构造代码

}

CRKDBMSView::~CRKDBMSView()
{
}

BOOL CRKDBMSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式


	return CView::PreCreateWindow(cs);
}



void CRKDBMSView::OnDraw(CDC* /*pDC*/)
{
	CRKDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

// TODO: 在此处为本机数据添加绘制代码 
}


// CRKDBMSView 打印

BOOL CRKDBMSView::OnPreparePrinting(CPrintInfo* pInfo)
{

	return DoPreparePrinting(pInfo);
}

void CRKDBMSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CRKDBMSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDBMSView 诊断

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


// CDBMSView 消息处理程序
