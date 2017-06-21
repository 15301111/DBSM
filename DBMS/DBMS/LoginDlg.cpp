// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "LoginDlg.h"
#include "SystemLogic.h"
#include "SystemDAO.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���
CSystemDAO sysDao;

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_sUsername(sysDao.GetCurrUserName(CString("log/u.temp")))
	, m_sPwd(sysDao.GetCurrUserName(CString("log/u1.temp")))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sUsername);
	DDX_Text(pDX, IDC_EDIT2, m_sPwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedRegister)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CSystemLogic sysLogic;
	if(sysLogic.VerifyLogin(m_sUsername,m_sPwd))
	{
		//��¼��ǰ��¼���û���
		sysDao.SaveCurrUserName(CString("log/u.temp"),m_sUsername);
		sysDao.SaveCurrPassword(CString("log/u1.temp"),m_sPwd);
		CDialogEx::OnOK();
		userTrue = 1;
	}
	else
		MessageBox(L"�û��������������",L"��ʾ",MB_OK);	
}

void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//
	::PostMessage(GetParentFrame()->GetSafeHwnd(), WM_CLOSE, 0, 0);
	//GetParentFrame()->PostMessage(WM_CLOSE);
	CDialogEx::OnClose();
}


void CLoginDlg::OnBnClickedRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegisterDlg reg;
	reg.DoModal();
}

void CLoginDlg::OnPaint()
{
	CPaintDC dc(this);   
	CRect rect;   
	GetClientRect(&rect);   
	CDC dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP1);   
	//IDB_BITMAP�����Լ���ͼ��Ӧ��ID
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	CDialogEx::OnPaint();
}
