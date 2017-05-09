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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CSystemLogic sysLogic;
	if(sysLogic.VerifyLogin(m_sUsername,m_sPwd))
	{
		//��¼��ǰ��¼���û���
		CSystemDAO sysDao;
		sysDao.SaveCurrUserName(CString("log/u.temp"),m_sUsername,m_sPwd);
		CDialogEx::OnOK();
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
