#pragma once
#include "afxcmn.h"
#include "FieldEntity.h"
#include "RecordEntity.h"
#include "TableView.h"
#include "afxwin.h"
// CRcdDialog �Ի���


class CRcdDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRcdDialog)

public:
	CRcdDialog(CWnd* pParent ,vector<CFieldEntity> &fieldList,CString &dbName,CString &tbName,int operType,vector<CString> &rcd);   // ��׼���캯��
	virtual ~CRcdDialog();

// �Ի�������
	enum { IDD = IDD_ADDRECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTableView *m_pTableView;
	vector<CFieldEntity> m_vFieldList;
	CRecordEntity *m_record;
	CListCtrl m_listCtl;

	int m_iOperType;
	vector<CString> m_rcd;

	int m_nRow;
	int m_nColumn;

	CString m_sDBName;
	CString m_sTableName;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit();
};
