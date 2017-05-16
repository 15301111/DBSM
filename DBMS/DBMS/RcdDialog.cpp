// AddRcdDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "RcdDialog.h"
#include "RecordLogic.h"
#include "afxdialogex.h"


// CRcdDialog �Ի���

IMPLEMENT_DYNAMIC(CRcdDialog, CDialogEx)

CRcdDialog::CRcdDialog(CWnd* pParent ,vector<CFieldEntity> &fieldList,CString &dbName,CString &tbName,int operType,vector<CString> &rcd)
	: CDialogEx(CRcdDialog::IDD, pParent)
{
	this->m_pTableView = (CTableView *)pParent;
	this->m_vFieldList = fieldList;
	this->m_sDBName = dbName;
	this->m_sTableName = tbName;
	this->m_iOperType = operType;
	this->m_rcd = rcd;
}

CRcdDialog::~CRcdDialog()
{
}

void CRcdDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listCtl);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CRcdDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRcdDialog::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CRcdDialog::OnNMClickList)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CRcdDialog::OnEnKillfocusEdit)
END_MESSAGE_MAP()


// CRcdDialog ��Ϣ�������


BOOL CRcdDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if(m_iOperType == OPERATE_ADD)
		this->SetWindowTextW(L"���Ӽ�¼");
	else
		this->SetWindowTextW(L"�޸ļ�¼");

	m_edit.ShowWindow(false);//�����������Ϊ���ɼ�

	LONG lStyle;
	lStyle = GetWindowLong(m_listCtl.m_hWnd, GWL_STYLE);  // ��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK;                              // �����ʾ��ʽλ
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtl.m_hWnd, GWL_STYLE, lStyle); 

	DWORD dwStyle = m_listCtl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;                          // ������
	m_listCtl.SetExtendedStyle(dwStyle);                  // ������չ���

	m_listCtl.InsertColumn(0, CString("�ֶ���"), LVCFMT_LEFT, 70);
	m_listCtl.InsertColumn(1, CString("����"), LVCFMT_LEFT, 70);
	m_listCtl.InsertColumn(2, CString("����"), LVCFMT_LEFT, 50);
	m_listCtl.InsertColumn(3, CString("�����"), LVCFMT_LEFT, 50);
	m_listCtl.InsertColumn(4, CString("Ψһ"), LVCFMT_LEFT, 50);
	m_listCtl.InsertColumn(5, CString("ֵ"), LVCFMT_LEFT, 100);

	
	for (int i=0; i<m_vFieldList.size(); ++i)
	{
		m_listCtl.InsertItem(i,m_vFieldList[i].GetName());
		m_listCtl.SetItemText(i, 1, CUtil::GetDataType(m_vFieldList[i].GetType()));
		m_listCtl.SetItemText(i, 2, CUtil::GetIcon(m_vFieldList[i].GetIsPK()));
		m_listCtl.SetItemText(i, 3, CUtil::GetIcon(m_vFieldList[i].GetIsNull()));
		m_listCtl.SetItemText(i, 4, CUtil::GetIcon(m_vFieldList[i].GetIsUnique()));
		if(m_iOperType == OPERATE_ADD)
			m_listCtl.SetItemText(i, 5, m_vFieldList[i].GetDefault());
		else
			m_listCtl.SetItemText(i, 5, m_rcd[i+1]);
	}

	//��ʼֵ����Ϊ5
	m_nColumn = 5;

	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRcdDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//m_record->SetValue();
	m_record = new CRecordEntity();
	CRecordLogic rcdLogic(m_sDBName,m_sTableName);
	bool isOK = true;
	//��֤�Ϸ���
	for (int i=0; i<m_vFieldList.size(); ++i)
	{
		CString val = m_listCtl.GetItemText(i, m_nColumn);
		int code = rcdLogic.IntegrityVerify(val,m_vFieldList[i]);
		if(code!=INTEGRITY_OK)
		{
			if(code == INTEGRITY_NOT_PK &&  m_iOperType == OPERATE_MODIFY)
			{
				if(val == m_rcd[i+1])
					m_record->SetValue(m_vFieldList[i].GetName(),val);
			}
			else
			{
				MessageBox(CUtil::GetError(code),CString("�����Դ���"),MB_OK|MB_ICONWARNING);
				isOK = false;
				break;
			}
		}
		else
		{
			m_record->SetValue(m_vFieldList[i].GetName(),val);
		}
	}

	if(isOK)
	{
		int code = 0;
		if (m_iOperType == OPERATE_ADD)
		{
			//��������
			code = rcdLogic.AddRecord(*m_record, m_vFieldList);
		}
		else
		{
			m_record->SetId(CUtil::StringToInteger(m_rcd[0]));
			//�޸�����
			code = rcdLogic.ModifyRecord(*m_record);
		}

		if(code==YES)
		{
			vector<CRecordEntity> rcdList = rcdLogic.GetRecordList();
			//ˢ����ʾ��¼��
			m_pTableView->DisplayRecords(rcdList,m_vFieldList);

			if(m_iOperType == OPERATE_ADD)
			{
				//��ռ�¼����
				int count = m_vFieldList.size();
				for (int i = 0; i < count; i++)
				{
					m_listCtl.SetItemText(i, m_nColumn,CString(""));
				}
			}
			else
				CDialogEx::OnOK();

		}
		else
			MessageBox(CUtil::GetError(code),CString("����"),MB_OK|MB_ICONWARNING);

		
	}

	//CDialogEx::OnOK();
}


void CRcdDialog::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtl.GetItemCount();

	if (m_nRow >= 0 && m_nColumn == 5 && m_nRow <= nCount)
	{
		// ���ý��տ��б��Ӧλ��
		CRect rtEdit, rtClient;
		m_listCtl.GetWindowRect(rtClient);
		ScreenToClient(rtClient);
		m_listCtl.GetSubItemRect(m_nRow, m_nColumn, LVIR_LABEL, rtEdit);
		rtEdit.left += rtClient.left + 0;
		rtEdit.top += rtClient.top + 0;
		rtEdit.bottom += 0;

		CString strTemp = m_listCtl.GetItemText(m_nRow, m_nColumn);
		int nLength = strTemp.GetLength();
		m_edit.SetWindowText(strTemp);
		m_edit.SetWindowPos(&wndTop, rtEdit.left, rtEdit.top, 100, 20, SWP_SHOWWINDOW);
		m_edit.SetSel(nLength, nLength);
		m_edit.ShowWindow(TRUE);
		m_edit.SetFocus();
	}

	*pResult = 0;
}


void CRcdDialog::OnEnKillfocusEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// ���û����������ͬ�����б���
	m_listCtl.SetItemText(m_nRow, m_nColumn, strValue);
}
