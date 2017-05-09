
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "Global.h"
#include "afxext.h"
#include "TableView.h"
#include "DBView.h"


class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	CTableView *m_pTableView;  //�ұ���ʾ������ͼָ��
	CDBView *m_pDBView;			//�����״ͼ����ָ��

	afx_msg void OnExit();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
protected:
	CSplitterWnd m_wndSplitter;
	
public:
	afx_msg void OnCrtDB();
	afx_msg void OnOpenDB();
	afx_msg void OnRenameDB();
	afx_msg void OnInitDB();
	afx_msg void OnLookLog();
};


