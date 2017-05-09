// DBView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBView.h"
#include "Resource.h"
#include "MainFrm.h"
#include "DBLogic.h"
#include "TableLogic.h"
#include "RecordLogic.h"
#include "TableView.h"
#include "FieldLogic.h"
#include "Util.h"
#include "ConditionQuery.h"
#include "SystemLogic.h"

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


// CDBView 诊断

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CTreeView::AssertValid();
	CString ss;
}

#ifndef _WIN32_WCE
void CDBView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG

