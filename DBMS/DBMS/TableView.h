#pragma once
#include "afxcmn.h"
#include "Global.h"
#include "FieldEntity.h"
#include "RecordEntity.h"

#define TABLEVIEW_VALID  0
#define TABLEVIEW_FIELD  1
#define TABLEVIEW_RECORD 2

// CTableView ��ͼ

class CTableView : public CListView
{
	DECLARE_DYNCREATE(CTableView)

protected:
	CTableView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTableView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	CListCtrl *m_ListCtrl;
public:
	virtual void OnInitialUpdate();
	int m_curView;       //�ж��ұߵı����ֶλ��Ǽ�¼

	int m_iRow;
	int m_iColumn;
	int m_iCount;

	void DisplayRecords(vector<CRecordEntity> &rcdlist,vector<CFieldEntity> &fieldList);
	void DisplayFields(vector<CFieldEntity> &fieldList);
	void ClearTable();
	afx_msg void OnAddField();
	afx_msg void OnDeleteField();
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddRecord();
	afx_msg void OnDeleteRecord();
	afx_msg void OnModifyRecord();
	afx_msg void OnModifyField();
};

