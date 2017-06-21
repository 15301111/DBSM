// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "RegisterDlg.h"
#include "SystemLogic.h"
#include "afxdialogex.h"


// CRegisterDlg �Ի���

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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������


void CRegisterDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_sUsername==L"")
	{
		MessageBox(L"�û�������Ϊ�գ�",L"��ʾ",MB_OK);
	}
	else
	{
		if (m_sPwd == m_sVPwd)
		{
			CSystemLogic sysLogic;
			if (sysLogic.Register(m_sUsername,m_sPwd))
			{
				MessageBox(L"ע��ɹ���",L"��ʾ",MB_OK);
				CDialogEx::OnOK();
			}
			else
				MessageBox(L"�û������ڣ�",L"��ʾ",MB_OK);
		}
		else
			MessageBox(L"�����������һ����",L"��ʾ",MB_OK);
	}
}

void CRegisterDlg::OnPaint()
{
	CPaintDC dc(this);   
	CRect rect;   
	GetClientRect(&rect);   
	CDC dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP2);   
	//IDB_BITMAP�����Լ���ͼ��Ӧ��ID
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	CDialogEx::OnPaint();
}
