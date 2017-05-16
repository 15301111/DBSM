// AddFieldDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "FieldDialog.h"
#include "RecordLogic.h"
#include "afxdialogex.h"
#include "FieldLogic.h"



// CFieldDialog 对话框

IMPLEMENT_DYNAMIC(CFieldDialog, CDialogEx)

CFieldDialog::CFieldDialog(CWnd* pParent /*=NULL*/,
								CString &dbName,
								CString &tbName,
								CFieldEntity &fieldEntity,
								int type)
	: CDialogEx(CFieldDialog::IDD, pParent)
	, m_sFieldName(_T(""))
	, m_sDefault(_T(""))
	, m_iLength(20)
	, m_sComm(_T(""))
	, m_bPK(FALSE)
	, m_bCanNull(TRUE)
	, m_bUnique(FALSE)
	, m_iSelType(INVALID)
	, m_dbName(dbName)
	, m_tbName(tbName)
	, m_iType(type)
	, m_fieldEntity(fieldEntity)
{
	m_pTableView = (CTableView *)pParent;
}

CFieldDialog::~CFieldDialog()
{
}

void CFieldDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sFieldName);
	DDV_MaxChars(pDX, m_sFieldName, 30);
	DDX_Text(pDX, IDC_EDIT4, m_sDefault);
	DDX_Text(pDX, IDC_EDIT3, m_iLength);
	DDX_Text(pDX, IDC_EDIT7, m_sComm);
	DDV_MaxChars(pDX, m_sComm, 50);
	DDX_Check(pDX, IDC_CHECK1, m_bPK);
	DDX_Check(pDX, IDC_CHECK2, m_bCanNull);
	DDX_Check(pDX, IDC_CHECK3, m_bUnique);
	DDX_Control(pDX, IDC_COMBO1, m_combType);
	DDX_Text(pDX, IDC_EDIT6, m_sMin);
	DDX_Text(pDX, IDC_EDIT5, m_sMax);
	
}


BEGIN_MESSAGE_MAP(CFieldDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFieldDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CFieldDialog::OnBnClickedPK)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFieldDialog::OnCbnSelchangeType)
END_MESSAGE_MAP()


// CFieldDialog 消息处理程序


void CFieldDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_iSelType = m_combType.GetCurSel()+1;
	if (m_sFieldName==""||m_iSelType==INVALID)
	{
		MessageBox(CString("字段名和类型不能为空！"),CString("警告"),MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		m_NewField.SetName(m_sFieldName);
		m_NewField.SetType(m_iSelType);
		m_NewField.SetIsPK(m_bPK);
		m_NewField.SetIsNull(m_bCanNull);
		m_NewField.SetIsUnique(m_bUnique);
		m_NewField.SetComment(m_sComm);
		m_NewField.SetLength(m_iLength);

		if(m_sMax!=L"")
			m_NewField.SetMax(CUtil::StringToInteger(m_sMax));
		else
			m_NewField.SetMax(-1);

		if(m_sMin!=L"")
			m_NewField.SetMin(CUtil::StringToInteger(m_sMin));
		else
			m_NewField.SetMin(-1);

		bool flag = true;

		if (m_NewField.GetMax()!=-1 && m_NewField.GetMin()!=-1 && m_NewField.GetMin()>=m_NewField.GetMax())
		{
			flag = false;
			MessageBox(L"最大值必须比最小值大！",L"警告",MB_OK);
		}

		//验证默认值的合法性
		switch (m_NewField.GetType())
		{
		case DB_INTEGER:
			if( m_NewField.GetMin()!=-1&&
				CUtil::StringToInteger(m_sDefault)<m_NewField.GetMin())
			{
				MessageBox(CUtil::GetError(INTEGRITY_OVER_RANGE),L"错误",MB_OK);
				flag = false;
			}

			if( m_NewField.GetMax()!=-1&&
				CUtil::StringToInteger(m_sDefault)>m_NewField.GetMax())
			{
				MessageBox(CUtil::GetError(INTEGRITY_OVER_RANGE),L"错误",MB_OK);
				flag = false;
			}

			break;
		case DB_DOUBLE:
			if( m_NewField.GetMin()!=-1&&
				CUtil::StringToInteger(m_sDefault)<m_NewField.GetMin())
			{
				MessageBox(CUtil::GetError(INTEGRITY_OVER_RANGE),L"错误",MB_OK);
				flag = false;
			}

			if( m_NewField.GetMax()!=-1&&
				CUtil::StringToInteger(m_sDefault)>m_NewField.GetMax())
			{
				MessageBox(CUtil::GetError(INTEGRITY_OVER_RANGE),L"错误",MB_OK);
				flag = false;
			}
		break;
		case DB_VARCHAR:
			if (m_sDefault.GetLength()>m_NewField.GetLength())
			{
				MessageBox(CUtil::GetError(INTEGRITY_TOO_LONG),L"错误",MB_OK);
				flag = false;
			}
		break;
		case DB_DATETIME:

		break;
		case DB_BOOL:

		break;
		default:
			break;
		}


		if (m_iType==OPERATE_ADD)
		{
			this->AddField(flag);
		}
		else
		{
			this->ModifyField(flag);
		}
	}
}


BOOL CFieldDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	//刷新初始化的值到控件
	
	
	m_combType.InsertString(0,CString("Integer"));
	m_combType.InsertString(1,CString("Bool"));
	m_combType.InsertString(2,CString("Double"));
	m_combType.InsertString(3,CString("Varchar"));
	m_combType.InsertString(4,CString("DateTime"));
	

	if (m_iType==OPERATE_MODIFY)
	{
		this->SetWindowTextW(L"修改字段");

		m_sFieldName = m_fieldEntity.GetName();

		m_combType.SetCurSel(m_fieldEntity.GetType()-1);
		m_iSelType = m_fieldEntity.GetType()-1;

		m_bPK = m_fieldEntity.GetIsPK();
		m_bCanNull = m_fieldEntity.GetIsNull();
		m_bUnique = m_fieldEntity.GetIsUnique();
		m_sComm = m_fieldEntity.GetComment();
		m_iLength = m_fieldEntity.GetLength();
		m_sDefault = m_fieldEntity.GetDefault();

		
		//GetDlgItem(IDC_EDIT3)->SetWindowTextW(CUtil::IntegerToString(m_iLength));
		//if(m_fieldEntity.GetMin()!=-1)
		//{
		//	GetDlgItem(IDC_EDIT6)->SetWindowTextW(
		//		CUtil::IntegerToString(m_fieldEntity.GetMin()));
		//}
		//if(m_fieldEntity.GetMax()!=-1)
		//{
		//	GetDlgItem(IDC_EDIT5)->SetWindowTextW(
		//		CUtil::IntegerToString(m_fieldEntity.GetMax()));
		//}


		if(m_bPK)
		{
			m_bCanNull = false;
			m_bUnique = true;
			//UpdateData(FALSE);
			GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		}
	
	}
	else
	{
		this->SetWindowTextW(L"增加字段");
		m_combType.SetCurSel(3);	//默认类型为varchar
		m_iSelType = 3;
	}

	UpdateData(FALSE);

	//根据type值更新窗口
	this->OnCbnSelchangeType();

	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}


void CFieldDialog::OnBnClickedPK()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新值到变量
	UpdateData(TRUE);
	if(m_bPK)
	{
		m_bCanNull = false;
		m_bUnique = true;
		UpdateData(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow();
		GetDlgItem(IDC_CHECK3)->EnableWindow();
	}
}


void CFieldDialog::OnCbnSelchangeType()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_iSelType = m_combType.GetCurSel()+1;
	switch (m_iSelType)
	{
	case DB_INTEGER:
		m_iLength = 0;
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow();
		GetDlgItem(IDC_EDIT6)->EnableWindow();
		break;
	case DB_BOOL:
		m_iLength = 0;
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		break;
	case DB_DATETIME:
		m_iLength = 0;
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		break;
	case DB_DOUBLE:
		m_iLength = 0;
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow();
		GetDlgItem(IDC_EDIT6)->EnableWindow();
		break;
	case DB_VARCHAR:
		m_iLength = 20;
		GetDlgItem(IDC_EDIT3)->EnableWindow();
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}


void CFieldDialog::AddField(bool flag)
{
	bool havePK = false;
	if(m_NewField.GetIsPK() == YES)
	{
		CFieldLogic fieldLogic(m_dbName,m_tbName);
		vector<CFieldEntity> fieldList = fieldLogic.GetFieldList();
		for (vector<CFieldEntity>::iterator ite=fieldList.begin();ite!=fieldList.end();++ite)
		{
			if(ite->GetIsPK()==YES)
			{
				
				MessageBox(L"该表已经有了主键！",L"错误",MB_OK);
				havePK = true; break;
					
			}
		}
	}

	if(flag&&!havePK)
	{
		m_NewField.SetDefault(m_sDefault);
		
		CRecordLogic rcdLogic(m_dbName,m_tbName);
		int code = rcdLogic.IntegrityVerify(m_NewField.GetDefault(),m_NewField); 
		if (code==INTEGRITY_OK)
		{
			//执行增加字段操作		
			CFieldLogic fieldLogic(m_dbName,m_tbName);
			code = fieldLogic.CreateField(m_NewField);
			if(code == YES)
			{
				vector<CFieldEntity> fieldList = fieldLogic.GetFieldList();
				m_pTableView->DisplayFields(fieldList);
			}
			else
				MessageBox(CUtil::GetError(code),CString("错误"),MB_OK);
			
		}else
			MessageBox(CUtil::GetError(code),CString("错误"),MB_OK);

		

		//CDialogEx::OnOK();
	}
}

void CFieldDialog::ModifyField(bool flag)
{
	

	bool havePK = false;
	CFieldLogic fieldLogic(m_dbName,m_tbName);
	vector<CFieldEntity> fieldList = fieldLogic.GetFieldList();
	if(m_NewField.GetIsPK() == YES)
	{
		for (vector<CFieldEntity>::iterator ite=fieldList.begin();ite!=fieldList.end();++ite)
		{
			if(ite->GetIsPK()==YES && ite->GetId()!= m_fieldEntity.GetId())
			{
				MessageBox(L"该表已经有了主键！",L"错误",MB_OK);
				havePK = true; break;
			}
		}
	}
	bool rangeSmaller = false,chageType = false;
	CRecordLogic rcdLogic(m_dbName,m_tbName);
	if(!rcdLogic.GetRecordList().empty())
	{
		//if (m_NewField.GetMax()<m_fieldEntity.GetMax()||
		//	m_NewField.GetMin()>m_fieldEntity.GetMin())
		//{
		//	rangeSmaller = true;
		//}
		if (m_NewField.GetType()!=m_fieldEntity.GetType())
		{
			MessageBox(L"当记录不为空时无法修改字段类型！",L"提示",MB_OK);
			chageType = true;
		}
		
	}

	if(flag && !rangeSmaller && !havePK && !chageType)
	{
		m_NewField.SetId(m_fieldEntity.GetId());
		m_NewField.SetDefault(m_sDefault);

		CRecordLogic rcdLogic(m_dbName,m_tbName);
		int code = rcdLogic.IntegrityVerify(m_NewField.GetDefault(),m_NewField); 
		if (code==INTEGRITY_OK)
		{
			code = fieldLogic.ModifyField(m_NewField);
			if (code == YES)
			{
				vector<CFieldEntity> fieldList = fieldLogic.GetFieldList();
				m_pTableView->DisplayFields(fieldList);
				CDialog::OnOK();
			}
			else
				MessageBox(CUtil::GetError(code),CString("错误"),MB_OK);
		}
		else
			MessageBox(CUtil::GetError(code),CString("错误"),MB_OK);
		
	}

}