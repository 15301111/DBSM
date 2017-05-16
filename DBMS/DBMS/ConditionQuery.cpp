// ConditionQuery.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "ConditionQuery.h"
#include "FieldLogic.h"
#include "RecordLogic.h"
#include "TableLogic.h"
#include "afxdialogex.h"

// CConditionQuery �Ի���

#define EQUAL 0
#define GREATER 1
#define LESSER 2

IMPLEMENT_DYNAMIC(CConditionQuery, CDialogEx)

CConditionQuery::CConditionQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConditionQuery::IDD, pParent)
{
	this->m_pParent = (CMainFrame *)pParent;
}

CConditionQuery::~CConditionQuery()
{
}

void CConditionQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_edit);
	DDX_Control(pDX, IDC_COMBO2, m_combox);
}


BEGIN_MESSAGE_MAP(CConditionQuery, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CConditionQuery::OnNMClickList)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CConditionQuery::OnCbnSelchangeCombox)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CConditionQuery::OnEnKillfocusEdit)
	ON_BN_CLICKED(IDOK, &CConditionQuery::OnBnClickedOk)
END_MESSAGE_MAP()


// CConditionQuery ��Ϣ�������


BOOL CConditionQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ʼ��listCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);   // ��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK;                              // �����ʾ��ʽλ
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle); 

	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;                          // ������
	m_listCtrl.SetExtendedStyle(dwStyle);                 // ������չ���

	m_listCtrl.InsertColumn(0, CString("�ֶ���"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(1, CString("�Ƚ�"), LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(2, CString("ֵ"), LVCFMT_LEFT, 100);


	CString dbname = m_pParent->m_pDBView->GetSelectedDBName();
	CString tbname = m_pParent->m_pDBView->GetSelectedTBName();
	CFieldLogic fieldLogic(dbname,tbname);
	m_list = fieldLogic.GetFieldList();
	for (int i = 0; i<m_list.size(); i++)
	{
		m_listCtrl.InsertItem(i,m_list[i].GetName());
		m_listCtrl.SetItemText(i,1,L"=");
	}
	
	m_combox.InsertString(0,L"=");
	m_combox.InsertString(1,L">");
	m_combox.InsertString(2,L"<");

	m_edit.ShowWindow(FALSE);
	m_combox.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CConditionQuery::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtrl.GetItemCount();

	if (m_nRow >= 0 && m_nRow <= nCount)
	{
		// ���ý��տ��б��Ӧλ��
		CRect rtEdit, rtClient;
		m_listCtrl.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		m_listCtrl.GetSubItemRect(m_nRow, m_nColumn, LVIR_LABEL, rtEdit);
		rtEdit.left += rtClient.left + 0;
		rtEdit.top += rtClient.top + 0;
		rtEdit.bottom += 0;

		if(m_nColumn == 2)
		{
			CString strTemp = m_listCtrl.GetItemText(m_nRow, m_nColumn);
			int nLength = strTemp.GetLength();
			m_edit.SetWindowText(strTemp);
			m_edit.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, 100, 20, SWP_SHOWWINDOW);
			m_edit.SetSel(nLength, nLength);
			m_edit.ShowWindow(TRUE);
			m_edit.SetFocus();
		}
		else if(m_nColumn == 1)
		{
			m_combox.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, 40, 20, SWP_SHOWWINDOW);
			//m_edit.SetSel(nLength, nLength);
			m_combox.ShowWindow(TRUE);
			m_combox.SetFocus();
		}


		
	}


	*pResult = 0;
}


void CConditionQuery::OnCbnSelchangeCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_compType = m_combox.GetCurSel();
	CString value;
	switch (m_compType)
	{
	case EQUAL:value = L"="; break;
	case GREATER:value = L">"; break;
	case LESSER:value = L"<"; break;
	default: break;
	}
	m_combox.ShowWindow(SW_HIDE);
	m_listCtrl.SetItemText(m_nRow,m_nColumn,value);
}


void CConditionQuery::OnEnKillfocusEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// ���û����������ͬ�����б���
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


void CConditionQuery::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vector<CString> compare;
	vector<CString> values;
	for (int i = 0; i<m_list.size(); i++)
	{
		compare.push_back(m_listCtrl.GetItemText(i,1));
		values.push_back(m_listCtrl.GetItemText(i,2));
	}

	CString dbname = m_pParent->m_pDBView->GetSelectedDBName();
	CString tbname = m_pParent->m_pDBView->GetSelectedTBName();
	CRecordLogic rcdLogic(dbname,tbname);
	CFieldLogic fieldLogic(dbname,tbname);
	vector<CRecordEntity> rcdList = rcdLogic.ConditionQuery(m_list,compare,values);
	m_pParent->m_pTableView->DisplayRecords(rcdList,fieldLogic.GetFieldList());

	CDialogEx::OnOK();
}
