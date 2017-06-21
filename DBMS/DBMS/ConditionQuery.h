#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MainFrm.h"

// CConditionQuery 对话框

class CConditionQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CConditionQuery)

public:
	CConditionQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConditionQuery();

// 对话框数据
	enum { IDD = IDD_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	afx_msg void OnPaint();
};
