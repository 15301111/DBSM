// AddRcdDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "RcdDialog.h"
#include "RecordLogic.h"
#include "afxdialogex.h"


// CRcdDialog 对话框

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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRcdDialog 消息处理程序


BOOL CRcdDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化

	if(m_iOperType == OPERATE_ADD)
		this->SetWindowTextW(L"增加记录");
	else
		this->SetWindowTextW(L"修改记录");

	m_edit.ShowWindow(false);//将输入框设置为不可见

	LONG lStyle;
	lStyle = GetWindowLong(m_listCtl.m_hWnd, GWL_STYLE);  // 获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK;                              // 清除显示方式位
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtl.m_hWnd, GWL_STYLE, lStyle); 

	DWORD dwStyle = m_listCtl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;                      // 选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;                          // 网格线
	m_listCtl.SetExtendedStyle(dwStyle);                  // 设置扩展风格

	m_listCtl.InsertColumn(0, CString("字段名"), LVCFMT_LEFT, 70);
	m_listCtl.InsertColumn(1, CString("类型"), LVCFMT_LEFT, 70);
	m_listCtl.InsertColumn(2, CString("主键"), LVCFMT_LEFT, 50);
	m_listCtl.InsertColumn(3, CString("允许空"), LVCFMT_LEFT, 50);
	m_listCtl.InsertColumn(4, CString("唯一"), LVCFMT_LEFT, 50);
	m_listCtl.InsertColumn(5, CString("值"), LVCFMT_LEFT, 100);

	
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

	//初始值设置为5
	m_nColumn = 5;

	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}


void CRcdDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//m_record->SetValue();
	m_record = new CRecordEntity();
	CRecordLogic rcdLogic(m_sDBName,m_sTableName);

	bool isOK = true;
	//验证合法性
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
				MessageBox(CUtil::GetError(code),CString("完整性错误"),MB_OK|MB_ICONWARNING);
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
			//插入数据
			code = rcdLogic.AddRecord(*m_record, m_vFieldList);
			
		}
		else
		{
			m_record->SetId(CUtil::StringToInteger(m_rcd[0]));
			//修改数据
			code = rcdLogic.ModifyRecord(*m_record);
		}

		if(code==YES)
		{
			vector<CRecordEntity> rcdList = rcdLogic.GetRecordList();
			//刷新显示记录表
			m_pTableView->DisplayRecords(rcdList,m_vFieldList);

			if(m_iOperType == OPERATE_ADD)
			{
				//清空记录数据
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
			MessageBox(CUtil::GetError(code),CString("错误"),MB_OK|MB_ICONWARNING);

		
	}

	CDialogEx::OnOK();
}


void CRcdDialog::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码


	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nRow = pNMListView->iItem;
	m_nColumn = pNMListView->iSubItem;
	DWORD nCount = m_listCtl.GetItemCount();

	if (m_nRow >= 0 && m_nColumn == 5 && m_nRow <= nCount)
	{
		// 设置接收框到列表对应位置
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
	// TODO: 在此添加控件通知处理程序代码
	CString strValue;
	m_edit.GetWindowText(strValue);
	m_edit.ShowWindow(SW_HIDE);

	// 把用户输入的内容同步到列表上
	m_listCtl.SetItemText(m_nRow, m_nColumn, strValue);
}

void CRcdDialog::OnPaint()
{
	CPaintDC dc(this);   
	CRect rect;   
	GetClientRect(&rect);   
	CDC dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP1);   
	//IDB_BITMAP是你自己的图对应的ID
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	CDialogEx::OnPaint();
}
