
// RKDBMSDoc.h : interface of the CRKDBMSDoc class
//


#pragma once

/*****************************************************
[ClassName] CRKDBMSDoc
[Function] Document class, implementation procedures related to the 
           interface of logic operation, and the data maintenance and management.
*****************************************************/
class CRKDBMSDoc : public CDocument
{
protected: // create from serialization only
	CRKDBMSDoc();
	DECLARE_DYNCREATE(CRKDBMSDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();       // New document
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CRKDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
