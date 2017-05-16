#pragma once
#include "FieldEntity.h"
#include "TableView.h"
#include "afxwin.h"

// CFieldDialog �Ի���

class CFieldDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFieldDialog)

public:
	CFieldDialog(CWnd* pParent,CString &dbname,CString &tbName,
					CFieldEntity &fieldEntity,int type);   // ��׼���캯��
	virtual ~CFieldDialog();

// �Ի�������
	enum { IDD = IDD_ADDFIELD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFieldEntity m_NewField;
	CString m_sFieldName;
	CString m_sDefault;
	int m_iLength;
	CString m_sComm;
	BOOL m_bPK;
	BOOL m_bCanNull;
	BOOL m_bUnique;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPK();
	afx_msg void OnCbnSelchangeType();
	void AddField(bool flag);
	void ModifyField(bool flag);
	CComboBox m_combType;
	int m_iSelType;
	CString m_sMin;
	CString m_sMax;

	CString m_dbName;
	CString m_tbName;
	int m_iType;
	CFieldEntity m_fieldEntity;
	CTableView *m_pTableView;
};

