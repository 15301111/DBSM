
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "Global.h"
#include "afxext.h"
#include "TableView.h"
#include "DBView.h"


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	CTableView *m_pTableView;  //右边显示数据视图指针
	CDBView *m_pDBView;			//左边树状图窗口指针

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


