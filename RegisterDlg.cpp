// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "RegisterDlg.h"
#include "SystemLogic.h"
#include "afxdialogex.h"


// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterDlg::IDD, pParent)
	, m_sUsername(_T(""))
	, m_sPwd(_T(""))
	, m_sVPwd(_T(""))
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sUsername);
	DDX_Text(pDX, IDC_EDIT2, m_sPwd);
	DDX_Text(pDX, IDC_EDIT3, m_sVPwd);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


void CRegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_sUsername==L"")
	{
		MessageBox(L"用户名不能为空！",L"提示",MB_OK);
	}
	else
	{
		if (m_sPwd == m_sVPwd)
		{
			CSystemLogic sysLogic;
			if (sysLogic.Register(m_sUsername,m_sPwd))
			{
				MessageBox(L"注册成功！",L"提示",MB_OK);
				CDialogEx::OnOK();
			}
			else
				MessageBox(L"用户名存在！",L"提示",MB_OK);
		}
		else
			MessageBox(L"两次密码必须一样！",L"提示",MB_OK);
	}
}
