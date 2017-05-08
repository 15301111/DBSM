// DBMSDoc.h : CDBMSDoc 类的接口
//

#pragma once

#include "DBEntity.h"	


class CRKDBMSDoc : public CDocument
{
protected:  // 仅从序列化创建
	CRKDBMSDoc();
	DECLARE_DYNCREATE(CRKDBMSDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();       // 创建新文件
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CRKDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	CDBEntity m_dbEntity;	
	CString m_strError;		

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
#endif // SHARED_HANDLERS
public:
	CDBEntity GetDBEntity();
	CString GetError();
	void SetError(CString strError);
};
