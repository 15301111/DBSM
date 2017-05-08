// DBView.cpp : implementation file
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBView.h"

#include "DBMSDoc.h"


// CDBView

IMPLEMENT_DYNCREATE(CDBView, CTreeView)

CDBView::CDBView()
{

}

CDBView::~CDBView()
{
}

BEGIN_MESSAGE_MAP(CDBView, CTreeView)
END_MESSAGE_MAP()


// CDBView diagnostics

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CDBView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


void CDBView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetDocument();


	CString strError = pDoc->GetError();

	if (strError.GetLength() != 0)
	{
		
		AfxMessageBox(strError);

		//设置异常信息为空
		pDoc->SetError(_T(""));
		return;
	}

	m_imageList.DeleteImageList();

	m_imageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 0, 4); 

	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_DATABASE));

	CTreeCtrl &treeCtrl = this->GetTreeCtrl();

	treeCtrl.SetImageList(&m_imageList, TVSIL_NORMAL);

	CString strDBName = pDoc->GetDBEntity().GetName();

	HTREEITEM hRoot = treeCtrl.InsertItem(strDBName, 0, 0, NULL);

	treeCtrl.Expand(hRoot, TVE_EXPAND);
}
