#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MainFrm.h"

// CConditionQuery �Ի���

class CConditionQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CConditionQuery)

public:
	CConditionQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConditionQuery();

// �Ի�������
	enum { IDD = IDD_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtrl;
	CEdit m_edit;
	CComboBox m_combox;
	CMainFrame *m_pParent;

	int m_nRow;
	int m_nColumn;
	int m_compType;
	vector<CFieldEntity> m_list;

	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombox();
	afx_msg void OnEnKillfocusEdit();
	afx_msg void OnBnClickedOk();
};
