// TableView.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "MainFrm.h"
#include "TableView.h"
#include "FieldLogic.h"
#include "FieldDialog.h"
#include "RcdDialog.h"
#include "RecordLogic.h"


// CTableView

IMPLEMENT_DYNCREATE(CTableView, CListView)

CTableView::CTableView()
{

}

CTableView::~CTableView()
{
}

BEGIN_MESSAGE_MAP(CTableView, CListView)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CTableView::OnNMRClick)
END_MESSAGE_MAP()


// CTableView 诊断

#ifdef _DEBUG
void CTableView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CTableView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTableView 消息处理程序


void CTableView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_ListCtrl = &GetListCtrl();

	LONG lStyle;
	lStyle = GetWindowLong(m_ListCtrl->m_hWnd, GWL_STYLE);   // 获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK;                              // 清除显示方式位
	lStyle |= LVS_REPORT;
	SetWindowLong(m_ListCtrl->m_hWnd, GWL_STYLE, lStyle); 

	DWORD dwStyle = m_ListCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // 选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;                          // 网格线
	m_ListCtrl->SetExtendedStyle(dwStyle);                   // 设置扩展风格

	//初始化的视图类型为非法视图
	m_curView = TABLEVIEW_VALID;

}



void CTableView::DisplayRecords(vector<CRecordEntity> &rcdlist,vector<CFieldEntity> &fieldList)
{
	m_curView = TABLEVIEW_RECORD;	//视图类型设置为记录视图

	//清除表
	//this->ClearTable();

	int columnNum = fieldList.size()+1;

	m_ListCtrl->InsertColumn(0, CString("#"), LVCFMT_LEFT, 0);
	for (int i = 1; i < columnNum; i++)
	{
		m_ListCtrl->InsertColumn(i, fieldList[i-1].GetName(), LVCFMT_LEFT, 150);
	}

	int rcdNum = rcdlist.size();
	for (int i = 0; i < rcdNum; i++)
	{
		m_ListCtrl->InsertItem(i,CUtil::IntegerToString(rcdlist[i].GetId()));
		for (int j = 1; j < columnNum; j++)
		{
			m_ListCtrl->SetItemText(i, j, rcdlist[i].GetValue(fieldList[j-1].GetName()));
		}
	}
}


void CTableView::DisplayFields(vector<CFieldEntity> &fieldList)
{
	m_curView = TABLEVIEW_FIELD; //视图类型设置为字段视图

	//this->ClearTable();

	m_ListCtrl->InsertColumn(0, CString("#"), LVCFMT_LEFT, 0);
	m_ListCtrl->InsertColumn(1, CString("字段名"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(2, CString("顺序"), LVCFMT_LEFT, 0);
	m_ListCtrl->InsertColumn(3, CString("类型"), LVCFMT_LEFT, 80);
	m_ListCtrl->InsertColumn(4, CString("长度"), LVCFMT_LEFT, 50);
	m_ListCtrl->InsertColumn(5, CString("最小值"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(6, CString("最大值"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(7, CString("默认值"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(8, CString("主键"), LVCFMT_LEFT, 40);
	m_ListCtrl->InsertColumn(9, CString("允许空值"), LVCFMT_LEFT, 70);
	m_ListCtrl->InsertColumn(10, CString("唯一值"), LVCFMT_LEFT, 60);
	m_ListCtrl->InsertColumn(11, CString("注释"), LVCFMT_LEFT, 100);

	for (int i = 0; i < fieldList.size(); ++i)
	{
		m_ListCtrl->InsertItem(i,CUtil::IntegerToString(fieldList[i].GetId()));
		m_ListCtrl->SetItemText(i, 1, fieldList[i].GetName());
		m_ListCtrl->SetItemText(i, 2, CUtil::IntegerToString(fieldList[i].GetOrder()));
		m_ListCtrl->SetItemText(i, 3, CUtil::GetDataType(fieldList[i].GetType()));
		m_ListCtrl->SetItemText(i, 4, CUtil::IntegerToString(fieldList[i].GetLength()));
		
		int tempInt = fieldList[i].GetMin();
		CString min = CUtil::IntegerToString(tempInt);
		if(fieldList[i].GetMin()==-1) min="";
		m_ListCtrl->SetItemText(i, 5, min);

		tempInt = fieldList[i].GetMax();
		CString max = CUtil::IntegerToString(tempInt);
		if(fieldList[i].GetMax()==-1) max="";
		m_ListCtrl->SetItemText(i, 6, max);
		

		m_ListCtrl->SetItemText(i, 7, fieldList[i].GetDefault());
		m_ListCtrl->SetItemText(i, 8, CUtil::GetIcon(fieldList[i].GetIsPK()));
		m_ListCtrl->SetItemText(i, 9, CUtil::GetIcon(fieldList[i].GetIsNull()));
		m_ListCtrl->SetItemText(i, 10, CUtil::GetIcon(fieldList[i].GetIsUnique()));
		m_ListCtrl->SetItemText(i, 11, fieldList[i].GetComment());
	}

}

void CTableView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_iRow = pNMListView->iItem;
	m_iColumn = pNMListView->iSubItem;
	m_iCount = m_ListCtrl->GetItemCount();


	CPoint point;
	GetCursorPos(&point);
	CMenu MyMenu;
	MyMenu.LoadMenu(IDR_MAINFRAME);

	if (m_iRow >= 0 && m_iRow < m_iCount)
	{
		m_ListCtrl->SetItemState(m_iRow, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		m_ListCtrl->SetSelectionMark(m_iRow);
		
	}
	else
	{
		if (m_curView == TABLEVIEW_FIELD)
		{
			MyMenu.GetSubMenu(3)->EnableMenuItem(2, MF_BYPOSITION | MF_DISABLED);
		}
		else if (m_curView == TABLEVIEW_RECORD)
		{
			MyMenu.GetSubMenu(4)->EnableMenuItem(2, MF_BYPOSITION | MF_DISABLED);
		}
	}

	if (m_curView == TABLEVIEW_FIELD)
	{
		CMenu* popup=MyMenu.GetSubMenu(3);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
	}
	else if (m_curView == TABLEVIEW_RECORD)
	{
		CMenu* popup=MyMenu.GetSubMenu(4);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
	}

	*pResult = 0;
}
