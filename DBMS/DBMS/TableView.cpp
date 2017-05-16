// TableView.cpp : ʵ���ļ�
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
	ON_COMMAND(ID_32780, &CTableView::OnAddField)
	ON_COMMAND(ID_32782, &CTableView::OnDeleteField)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CTableView::OnNMRClick)
	ON_COMMAND(ID_32783, &CTableView::OnAddRecord)
	ON_COMMAND(ID_32785, &CTableView::OnDeleteRecord)
	ON_COMMAND(ID_32784, &CTableView::OnModifyRecord)
	ON_COMMAND(ID_32781, &CTableView::OnModifyField)
END_MESSAGE_MAP()


// CTableView ���

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


// CTableView ��Ϣ�������


void CTableView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_ListCtrl = &GetListCtrl();

	LONG lStyle;
	lStyle = GetWindowLong(m_ListCtrl->m_hWnd, GWL_STYLE);   // ��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK;                              // �����ʾ��ʽλ
	lStyle |= LVS_REPORT;
	SetWindowLong(m_ListCtrl->m_hWnd, GWL_STYLE, lStyle); 

	DWORD dwStyle = m_ListCtrl->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;                          // ������
	m_ListCtrl->SetExtendedStyle(dwStyle);                   // ������չ���

	//��ʼ������ͼ����Ϊ�Ƿ���ͼ
	m_curView = TABLEVIEW_VALID;

}



void CTableView::DisplayRecords(vector<CRecordEntity> &rcdlist,vector<CFieldEntity> &fieldList)
{
	m_curView = TABLEVIEW_RECORD;	//��ͼ��������Ϊ��¼��ͼ

	//�����
	this->ClearTable();

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
	m_curView = TABLEVIEW_FIELD; //��ͼ��������Ϊ�ֶ���ͼ

	this->ClearTable();

	m_ListCtrl->InsertColumn(0, CString("#"), LVCFMT_LEFT, 0);
	m_ListCtrl->InsertColumn(1, CString("�ֶ���"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(2, CString("˳��"), LVCFMT_LEFT, 0);
	m_ListCtrl->InsertColumn(3, CString("����"), LVCFMT_LEFT, 80);
	m_ListCtrl->InsertColumn(4, CString("����"), LVCFMT_LEFT, 50);
	m_ListCtrl->InsertColumn(5, CString("��Сֵ"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(6, CString("���ֵ"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(7, CString("Ĭ��ֵ"), LVCFMT_LEFT, 100);
	m_ListCtrl->InsertColumn(8, CString("����"), LVCFMT_LEFT, 40);
	m_ListCtrl->InsertColumn(9, CString("�����ֵ"), LVCFMT_LEFT, 70);
	m_ListCtrl->InsertColumn(10, CString("Ψһֵ"), LVCFMT_LEFT, 60);
	m_ListCtrl->InsertColumn(11, CString("ע��"), LVCFMT_LEFT, 100);

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


void CTableView::ClearTable()
{
	//��ձ����ݼ���ͷ
	m_ListCtrl->DeleteAllItems();
	while (m_ListCtrl->GetHeaderCtrl()->GetItemCount())
	{
		m_ListCtrl->DeleteColumn(0);
	}
	
}


void CTableView::OnAddField()
{
	// TODO: �ڴ���������������
	CString dbName,tbName;
	((CMainFrame *)GetParentFrame())->m_pDBView->GetDBAndTableName(dbName,tbName);

	CFieldDialog addFieldDlg(this,dbName,tbName,CFieldEntity(),OPERATE_ADD);
	addFieldDlg.DoModal();
}


void CTableView::OnDeleteField()
{
	// TODO: �ڴ���������������

	if(m_curView == TABLEVIEW_FIELD)
	{
		CString fieldName;
		POSITION pos = m_ListCtrl->GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			if (MessageBox(CString("ȷ��Ҫɾ�����ֶΣ�"),CString("ɾ���ֶ�"),MB_OKCANCEL)==IDOK)
			{
				int nItem = m_ListCtrl->GetNextSelectedItem(pos);
				fieldName =  m_ListCtrl->GetItemText(nItem,1);

				CString dbName,tbName;
				((CMainFrame *)GetParentFrame())->m_pDBView->GetDBAndTableName(dbName,tbName);
				CFieldLogic fieldLogic(dbName,tbName);

				int code = fieldLogic.DeleteField(fieldName);
				if(code == YES)
				{
					vector<CFieldEntity> fieldList = fieldLogic.GetFieldList();
					this->DisplayFields(fieldList);
				}
				else
				{
					MessageBox(CUtil::GetError(code),CString("����"),MB_OK);
				}

			}

		}
	}

	

}


void CTableView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CTableView::OnAddRecord()
{
	// TODO: �ڴ���������������


	CString dbName,tbName;
	((CMainFrame *)GetParentFrame())->m_pDBView->GetDBAndTableName(dbName,tbName);

	CFieldLogic fieldLogic(dbName,tbName);
	CRcdDialog addRcdDlg(this,
					fieldLogic.GetFieldList(),
					dbName,
					tbName,
					OPERATE_ADD,
					vector<CString>());

	addRcdDlg.DoModal();
	//addRcdDlg.ShowWindow(TRUE);

}


void CTableView::OnDeleteRecord()
{
	// TODO:  �ڴ���������������

	if (m_iRow < m_iCount && m_iRow >= 0 && m_curView == TABLEVIEW_RECORD)
	{
		if(MessageBox(CString("ȷ��ɾ���ü�¼��"), CString("ɾ����¼"), MB_OKCANCEL)==IDOK)
		{
			CString dbName, tbName;
			CDBView *pDBView = ((CMainFrame *)GetParentFrame())->m_pDBView;
			pDBView->GetDBAndTableName(dbName, tbName);

			CRecordLogic rcdLogic(dbName, tbName);
			int code = rcdLogic.DeleteRecord(CUtil::StringToInteger(m_ListCtrl->GetItemText(m_iRow, 0)));
			if (code == YES)
			{
				pDBView->OnLookTable();
			}
			else
				MessageBox(CUtil::GetError(code), CString("����"), MB_OK);
		}

	}
}


void CTableView::OnModifyRecord()
{
	// TODO:  �ڴ���������������
	if (m_iRow < m_iCount && m_iRow >= 0 && m_curView == TABLEVIEW_RECORD)
	{
		int columnNum = m_ListCtrl->GetHeaderCtrl()->GetItemCount();
		vector<CString> list;
		for (int i = 0; i < columnNum; i++)
		{
			list.push_back(m_ListCtrl->GetItemText(m_iRow,i));
		}
		CString dbName,tbName;
		((CMainFrame *)GetParentFrame())->m_pDBView->GetDBAndTableName(dbName,tbName);
		CFieldLogic fieldLogic(dbName,tbName);
		CRcdDialog modifyRcdDlg(this,
					fieldLogic.GetFieldList(),
					dbName,
					tbName,
					OPERATE_MODIFY,
					list);
		modifyRcdDlg.DoModal();
	}
	
}


void CTableView::OnModifyField()
{
	// TODO: �ڴ���������������
	if (m_iRow < m_iCount && m_iRow >= 0 && m_curView == TABLEVIEW_FIELD)
	{
		CString dbName,tbName;
		((CMainFrame *)GetParentFrame())->m_pDBView->GetDBAndTableName(dbName,tbName);
		CFieldEntity field( CUtil::StringToInteger(m_ListCtrl->GetItemText(m_iRow,0)),
							m_ListCtrl->GetItemText(m_iRow,1),
							CUtil::TypeToInt(m_ListCtrl->GetItemText(m_iRow,3)),
							CUtil::StringToInteger(m_ListCtrl->GetItemText(m_iRow,4)),
							CUtil::IconToInt(m_ListCtrl->GetItemText(m_iRow,8)),
							CUtil::IconToInt(m_ListCtrl->GetItemText(m_iRow,9)),
							CUtil::IconToInt(m_ListCtrl->GetItemText(m_iRow,10)),
							m_ListCtrl->GetItemText(m_iRow,11));

		
		field.SetMin(CUtil::StringToInteger(m_ListCtrl->GetItemText(m_iRow,5)));
		field.SetMax(CUtil::StringToInteger(m_ListCtrl->GetItemText(m_iRow,6)));
		field.SetDefault(m_ListCtrl->GetItemText(m_iRow,7));

		//MessageBox(CUtil::DoubleToString(field.GetMin()),L"",MB_OK);

		CFieldDialog modifyFieldDlg(this,dbName,tbName,field,OPERATE_MODIFY);
		modifyFieldDlg.DoModal();
	}

}
