
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "DBMS.h"
#include "LoginDlg.h"
#include "MainFrm.h"
#include "BinaryFile.h"
#include "DBView.h"
#include "TableView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_32771, &CMainFrame::OnExit)
	ON_COMMAND(ID_32772, &CMainFrame::OnCrtDB)
	ON_COMMAND(ID_32778, &CMainFrame::OnOpenDB)
	ON_COMMAND(ID_32773, &CMainFrame::OnRenameDB)
	ON_COMMAND(ID_32790, &CMainFrame::OnInitDB)
	ON_COMMAND(ID_32791, &CMainFrame::OnLookLog)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: �������Ҫ��ͣ������������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.lpszName = CString("���ݿ����ϵͳ");   // �ı䴰�ڱ���
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������

void CMainFrame::OnExit()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0); 
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDBView), CSize(160, 200), pContext))
		return FALSE;
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTableView), CSize(160, 200), pContext))
		return FALSE;

	m_pTableView = (CTableView *)m_wndSplitter.GetPane(0,1);
	m_pDBView = (CDBView *)m_wndSplitter.GetPane(0,0);



	return TRUE;
}


void CMainFrame::OnCrtDB()
{
	// TODO: �ڴ���������������
	m_pDBView->OnCrtDB();
}


void CMainFrame::OnOpenDB()
{
	// TODO: �ڴ���������������
	m_pDBView->OnOpenDB();
}


void CMainFrame::OnRenameDB()
{
	// TODO: �ڴ���������������
	m_pDBView->OnRenameDB();
}


void CMainFrame::OnInitDB()
{
	// TODO: �ڴ���������������
	if(MessageBox(L"�˲���������������ϣ�ȷ��Ҫ��ʼ���⣿",L"��ʾ",MB_OKCANCEL)==IDOK)
	{
		CUtil::DeleteFolder(DEFAULT_ROOT);
		CUtil::CreateFolder(DEFAULT_ROOT);
		vector<CString> str;
		str.push_back(CString("0"));
		if(CBinaryFile::Write(DEFAULT_SYS_FILE,str))
		{
			//ɾ����״ͼ�е����ݿ���ʾ
			HTREEITEM hNextItem;
			HTREEITEM hPreItem = m_pDBView->m_pTreeCtrl->GetRootItem();
			while (hPreItem != NULL)
			{
				hNextItem = m_pDBView->m_pTreeCtrl->GetNextItem(hPreItem, TVGN_NEXT);
				m_pDBView->m_pTreeCtrl->DeleteItem(hPreItem);
				hPreItem = hNextItem;
			}

			MessageBox(L"���ݿ��ʼ���ɹ���",L"��ʾ",MB_OK);
		}
		else
			MessageBox(L"���ݿ��ʼ��ʧ�ܣ�",L"��ʾ",MB_OK);
	}
}


void CMainFrame::OnLookLog()
{
	// TODO: �ڴ���������������

	m_pDBView->OnLookLog();
}
