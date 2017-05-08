
// DBMSView.h : CDBMSView 类的接口
//

#pragma once
class CRKDBMSDoc; 

class CRKDBMSView : public CView
{
protected: 
	CRKDBMSView();
	DECLARE_DYNCREATE(CRKDBMSView)


public:
	CRKDBMSDoc* GetDocument() const;   // 获取视图文件


public:


public:
	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); 
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


public:
	virtual ~CRKDBMSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  //DBMSView.cpp 中的调试版本
inline CRKDBMSDoc* CRKDBMSView::GetDocument() const
   { return reinterpret_cast<CRKDBMSDoc*>(m_pDocument); }
#endif

