
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RKDBMS.h"

#include "MainFrm.h"
#include "DBView.h"
#include "RKDBMSView.h"
#include "RKDBMSDoc.h"
#include "NewTableDlg.h"
#include "FieldDlg.h"
#include "Global.h"
#include "TableView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(IDM_NEW_TABLE, &CMainFrame::OnNewTable)
	ON_COMMAND(IDM_ADD_FIELD, &CMainFrame::OnAddField)
	ON_COMMAND(IDM_OPEN_DATABASE, &CMainFrame::OnOpenDatabase)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_DATABASE, &CMainFrame::OnUpdateOpenDatabase)
	ON_COMMAND(IDM_MODIFY_TABLE, &CMainFrame::OnEditTable)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_RUANKO_TITLE,        // The author information pane
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// View type
#define DEFAULT 0	// Default view
#define TABLE   1	// Table structure view

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bOpenDatabase = FALSE;
}

CMainFrame::~CMainFrame()
{
}

/************************************************************************
[FunctionName]	OnCreate
[Function]	The function of creating framework, called by the system, which is used to initialize the menu bar, toolbar bar and status bar
[Argument]	LPCREATESTRUCT lpCreateStruct: Create a framework of information structure
[ReturnedValue] int: Zero if the operation is successful; otherwise non-zero.
************************************************************************/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Set window text
	this->SetTitle(_T("DBMS"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

/***************************************************************
[FunctionName]	OnCreateClient
[Function]	Split window
[Argument]	LPCREATESTRUCT lpcs: A pointer to a Windows CREATESTRUCT structure.
		CCreateContext* pContext:A pointer to a CCreateContext structure.
[ReturnedValue] BOOL: TRUE if successful; otherwise FALSE
***************************************************************/
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// Create a static split window, the view can be divided into two columns
	if (!m_wndSpliter.CreateStatic(this, 1, 2))
	{
		AfxMessageBox(_T("Failed to split window!"));
		return FALSE;
	}

	// Add view to the separated window
	if(!m_wndSpliter.CreateView(0, 0, RUNTIME_CLASS(CDBView), CSize(200, 0), pContext))
	{
		return FALSE;
	}
	if (!m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CRKDBMSView), CSize(0,0), pContext))
	{
		return FALSE;
	}


	return TRUE;

//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

/************************************************
[FunctionName]	OnNewTable
[Function]	COMMAND message response function of "New table" menu , response to the functionality of creating talbe 
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnNewTable()
{
	if (m_bOpenDatabase == TRUE)
	{
		// Create and display the new table dialog
		CNewTableDlg dlg;
		int nRes = dlg.DoModal();

		// nRes==IDOK£¬Confirm the name of the table
		if (nRes == IDOK)
		{
			//	Get the object of document
			CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();

			// Get the existed table
			int nCount = pDoc->GetTableNum();
			for (int i = 0; i < nCount; i++)
			{
				CString strName = pDoc->GetTable(i)->GetName();
				if (dlg.m_strName == strName)
				{
					AfxMessageBox(_T("The table has been existed£¡"));
					return;
				}
			}

			// Create the table according to the input table name
			CTableEntity* pTable = pDoc->CreateTable(dlg.m_strName);
			// Get the exception information
			CString strError = pDoc->GetError();
			// If there has exception information, prompt exception
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}
			// If the added table is not empty, update the view
			if (pTable != NULL)
			{
				// Switch to the table view
				SwitchView(TABLE);

				// Update view
				pDoc->UpdateAllViews(NULL, UPDATE_CREATE_TABLE, pTable);
			}
		}
	}

}

/************************************************
[FunctionName]	OnAddField
[Function]	COMMAND message response function of "Add Field" menu , response to the functionality of adding field 
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnAddField()
{
	// Get the object of document
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
	CTableEntity* pTable = pDoc->GetEditTable();
	if (pTable != NULL)
	{	
		// Create and display the fields dialog box
		CFieldDlg dlg;
		int nRes = dlg.DoModal();

		if (nRes == IDOK)
		{
			CFieldEntity field = dlg.GetField();
			int nCount = pTable->GetFieldNum();
			for (int i = 0; i < nCount; i++)
			{
				if (field.GetName() == pTable->GetFieldAt(i)->GetName())
				{
					AfxMessageBox(_T("The field has been existed£¡"));
					return;
				}
			}
			// Add field
			CFieldEntity* pField = pDoc->AddField(field);

			// If there has exception information, prompt exception
			CString strError = pDoc->GetError();
			if (strError.GetLength() != 0)
			{
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}

			// If the added field is not empty, update the view
			if (pField != NULL)
			{
				pDoc->UpdateAllViews(NULL, UPDATE_ADD_FIELD, pField);
			}
		}
	}

}


/************************************************
[FunctionName]	SwitchView
[Function]	Switch view
[Argument]	int nViewType: view type
[ReturnedValue]	void
************************************************/
void CMainFrame::SwitchView(int nViewType)
{
	// Get the size of the original window
	CRect rt;
	CView* pOldView = (CView*)m_wndSpliter.GetPane(0, 1);	
	pOldView->GetClientRect(&rt);

	// Get the context
	CCreateContext context;
	context.m_pCurrentDoc = pOldView->GetDocument();
	context.m_pCurrentFrame = this;

	// Delete the original view
	m_wndSpliter.DeleteView(0, 1);

	// Depending on the type of view, create a new view
	switch(nViewType)
	{
	case TABLE:	// Table structure view
		{
			// Add a new view
			context.m_pNewViewClass = RUNTIME_CLASS(CTableView);
			m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CTableView), rt.Size(), &context);
		}
		break;
	case DEFAULT: // Default view
		{
			// Add new view
			context.m_pNewViewClass = RUNTIME_CLASS(CTableView);
			m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CRKDBMSView), rt.Size(), &context);
		}
		break;
	default:
		break;
	}

	// Update view
	CView* pCurView = (CView*)m_wndSpliter.GetPane(0, 1);
	pCurView->OnInitialUpdate();

	// Update window
	m_wndSpliter.RecalcLayout();
}

/************************************************
[FunctionName]	OnOpenDatabase
[Function]	COMMAND message response function of opening database menu , response to the functionality of opening database
[Argument]	int nViewType: View type
[ReturnedValue]	void
************************************************/
void CMainFrame::OnOpenDatabase()
{
	// Get the pointer to the document
	CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();

	// Read table
	pDoc->LoadTables();

	// Decide whether has exception
	CString strError = pDoc->GetError();
	if(strError.GetLength() > 0)
	{
		AfxMessageBox(strError);
		pDoc->SetError(_T(""));
		return;
	}

	// The database has been opened
	m_bOpenDatabase = TRUE;

	// Update view
	pDoc->UpdateAllViews(NULL, UPDATE_OPEN_DATABASE, NULL);

}

/************************************************
[FunctionName]	OnUpdateOpenDatabase
[Function]	Change the display status of menu item
[Argument]	CCmdUI *pCmdUI: The object to receive command
[ReturnedValue]	void
************************************************/
void CMainFrame::OnUpdateOpenDatabase(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bOpenDatabase);
}

/************************************************
[FunctionName]	OnEditTable
[Function]	COMMAND message response function of altering table menu , display the table structure
[Argument]	void
[ReturnedValue]	void
************************************************/
void CMainFrame::OnEditTable()
{
	if (m_bOpenDatabase == TRUE)
	{
		// Create new table
		CRKDBMSDoc* pDoc = (CRKDBMSDoc*)this->GetActiveDocument();
		CTableEntity* pTable = pDoc->GetEditTable();
		if (pTable != NULL)
		{
			// Switch window
			SwitchView(TABLE);	

			pDoc->UpdateAllViews(NULL, UPDATE_EDIT_TABLE,  pTable);
		}	
	}
}
