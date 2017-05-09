// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "LoginDlg.h"
#include "SystemLogic.h"
#include "SystemDAO.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_sUsername(_T("root"))
	, m_sPwd(_T(""))
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
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CSystemLogic sysLogic;
	if(sysLogic.VerifyLogin(m_sUsername,m_sPwd))
	{
		//记录当前登录的用户名
		CSystemDAO sysDao;
		sysDao.SaveCurrUserName(CString("log/u.temp"),m_sUsername,m_sPwd);
		CDialogEx::OnOK();
	}
	else
		MessageBox(L"用户名或者密码错误！",L"提示",MB_OK);

	
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//
	::PostMessage(GetParentFrame()->GetSafeHwnd(), WM_CLOSE, 0, 0);
	//GetParentFrame()->PostMessage(WM_CLOSE);
	CDialogEx::OnClose();
}


void CLoginDlg::OnBnClickedRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegisterDlg reg;
	reg.DoModal();
}
