#pragma once



class CDBView : public CTreeView
{
	DECLARE_DYNCREATE(CDBView)

protected:
	CDBView();          
	virtual ~CDBView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();	//视图初始化函数

private:
	CImageList m_imageList;	//	树视图
};


