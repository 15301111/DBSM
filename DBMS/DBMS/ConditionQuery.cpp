// ConditionQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "ConditionQuery.h"
#include "FieldLogic.h"
#include "RecordLogic.h"
#include "TableLogic.h"
#include "afxdialogex.h"

// CConditionQuery 对话框

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


// CConditionQuery 消息处理程序


BOOL CConditionQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化listCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);   // 获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK;                              // 清除显示方式位
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle); 

	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // 选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;                          // 网格线
	m_listCtrl.SetExtendedStyle(dwStyle);                 // 设置扩展风格

	m_listCtrl.InsertColumn(0, CString("字段名"), LVCFMT_LEFT, 60);
	m_listCtrl.InsertColumn(1, CString("比较"), LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(2, CString("值"), LVCFMT_LEFT, 100);


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
	// 异常: OCX 属性页应返回 FALSE
}


void CConditionQuery::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtrl.GetItemCount();

	if (m_nRow >= 0 && m_nRow <= nCount)
	{
		// 设置接收框到列表对应位置
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// 把用户输入的内容同步到列表上
	m_listCtrl.SetItemText(m_nRow, m_nColumn, strValue);
}


void CConditionQuery::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
