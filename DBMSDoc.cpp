
// RKDBMSDoc.cpp : implementation of the CRKDBMSDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RKDBMS.h"
#endif

#include "RKDBMSDoc.h"

#include "DBLogic.h"
#include "TableLogic.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRKDBMSDoc

IMPLEMENT_DYNCREATE(CRKDBMSDoc, CDocument)

BEGIN_MESSAGE_MAP(CRKDBMSDoc, CDocument)
END_MESSAGE_MAP()


// CRKDBMSDoc construction/destruction

CRKDBMSDoc::CRKDBMSDoc()
{
	m_strError = _T("");	//	Initialize the exception information
	m_pEditTable = NULL;

}

CRKDBMSDoc::~CRKDBMSDoc()
{
}

/***************************************************************
[FunctionName] OnNewDocument
[Function] Create new document
[Argument] void
[ReturnedValue] BOOL:TRUE is the operation is successful, otherwise FALSE
***************************************************************/
BOOL CRKDBMSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_dbEntity.SetName(_T("Ruanko"));	// The default database is Ruanko

	CDBLogic dbLogic;
	try
	{
		//	Decide whether exists the database
		if (dbLogic.GetDatabase(m_dbEntity) == false)
		{
			//	Decide whether creates the database successfully
			if (dbLogic.CreateDatabase(m_dbEntity) == false)
			{
				//	If creates failure, throw an exception
				throw new CAppException(_T("Failed to create database£¡"));
			}

		}

		// Set the document title bar
		CString strTitle;
		strTitle.Format(_T("Database(%s)"), m_dbEntity.GetName());
		this->SetTitle(strTitle);
	}
	catch (CAppException* e)	// Catch custom exception
	{
		// Throw exception
		m_strError = e->GetErrorMessage();
		delete e;
	}
	
	return TRUE;
}
// CRKDBMSDoc serialization

void CRKDBMSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRKDBMSDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

#endif // SHARED_HANDLERS

// CRKDBMSDoc diagnostics

#ifdef _DEBUG
void CRKDBMSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRKDBMSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRKDBMSDoc commands

/*****************************************************
[FunctionName] GetDBEntity
[Function]	Get the database entity
[Argument]	void
[ReturnedValue] CDBEntity: Database entity
*****************************************************/
CDBEntity CRKDBMSDoc::GetDBEntity()
{
	return m_dbEntity;
}

/*****************************************************
[FunctionName] GetError
[Function]	Get exception information
[Argument]	void
[ReturnedValue] CString: Exception information string
*****************************************************/
CString CRKDBMSDoc::GetError()
{
	//	Remove white space characters
	m_strError.TrimLeft();
	m_strError.TrimRight();

	return m_strError;
}

/*****************************************************
[FunctionName] SetError
[Function]	Set exception information
[Argument]	CString strError: Exception information string
[ReturnedValue] void
*****************************************************/
void CRKDBMSDoc::SetError(CString strError)
{
	m_strError = strError;
}

/*****************************************************
[FunctionName] CreateTable
[Function]	Create table
[Argument]	CString strName: Table name
[ReturnedValue] CTableEntity*: Table entity object pointer, if create failure for NULL said
*****************************************************/
CTableEntity* CRKDBMSDoc::CreateTable(CString strName)
{
	CTableEntity* pTable = new CTableEntity();
	pTable->SetName(strName);
	CTableLogic tbLogic;
	try
	{
		// Decide whether creates table successfully
		if (tbLogic.CreateTable(m_dbEntity.GetName(), *pTable) == true)
		{
			// If creates table successfully, the created table information would be saved to the array.
			m_arrTable.Add(pTable);
		}
		else
		{
			// If creates failure, release the memory allocated by new
			delete pTable;
			pTable = NULL;
		}
	}
	catch(CAppException* e)	// Catch exception
	{
		// If there is exception, release the memory allocated by new
		if (pTable != NULL)
		{
			delete pTable;
			pTable = NULL;
		}
		// Get exception information
		m_strError = e->GetErrorMessage();
		// Delete exception
		delete e;
	}

	return pTable;
}

/*****************************************************
[FunctionName] OnCloseDocument
[Function]	Close document
[Argument]	void
[ReturnedValue] void
*****************************************************/
void CRKDBMSDoc::OnCloseDocument()
{
	// Get the number of elements in the table array.
	int nCount = m_arrTable.GetCount();

	// Traverse the table array
	for (int i = 0; i < nCount; i++)
	{
		// Release the elements in the array
		CTableEntity* pTable = (CTableEntity*)m_arrTable.GetAt(i);
		if (pTable != NULL)
		{
			delete pTable;
			pTable = NULL;
		}
	}
	// Empty table array
	m_arrTable.RemoveAll();

	CDocument::OnCloseDocument();
}

/*****************************************************
[FunctionName] GetEditTable
[Function]	Gets the current table object
[Argument]	void
[ReturnedValue] CTableEntity*: Pointer to the current form
*****************************************************/
CTableEntity* CRKDBMSDoc::GetEditTable()
{
	return m_pEditTable;
}

/*****************************************************
[FunctionName] AddField
[Function]	Add field
[Argument]	CFieldEntity &field: Field information entity
[ReturnedValue] void
*****************************************************/
CFieldEntity* CRKDBMSDoc::AddField(CFieldEntity &field)
{
	CTableLogic tbLogic;
	try
	{
		// Add a field
		if(tbLogic.AddField(m_dbEntity.GetName(), *m_pEditTable, field) == false)
		{
			return NULL;
		}

		// Get field number
		int nCount = m_pEditTable->GetFieldNum();

		// Return the last field
		CFieldEntity* pField = m_pEditTable->GetFieldAt(nCount - 1);
		return pField;
	}
	catch(CAppException* e)
	{
		m_strError = e->GetErrorMessage();
		delete e;
		return NULL;
	}
}

/*****************************************************
[FunctionName] SetEditTable
[Function]	Set the table editor
[Argument]	CString strTableName: Table name
[ReturnedValue] void
*****************************************************/
void CRKDBMSDoc::SetEditTable(CString strTableName)
{
	if (strTableName.GetLength() > 0)
	{
		// Get the number of the table
		int nCount = m_arrTable.GetCount();

		// Find the table information of the same table name
		for (int i = 0; i  < nCount; i++)
		{
			CTableEntity* pTable = m_arrTable.GetAt(i);
			if (pTable->GetName().CollateNoCase(strTableName) == 0)
			{
				m_pEditTable = pTable;
				CString strTitle;
				strTitle.Format(_T("Table(%s)"), m_pEditTable->GetName());
				this->SetTitle(strTitle);
				return;
			}
		}
	}
	else
	{
		m_pEditTable = NULL;
		CString strTitle;
		strTitle.Format(_T("Database(%s)"), m_dbEntity.GetName());
		this->SetTitle(strTitle);
	}	
}

/*****************************************************
[FunctionName] LoadTables
[Function]	Load tables in the database
[Argument]	void
[ReturnedValue] void
*****************************************************/
void CRKDBMSDoc::LoadTables(void)
{
	CTableLogic tbLogic;

	try
	{
		// Get the number of table in the table array
		int nCount = m_arrTable.GetCount();
		for (int i = 0; i < nCount; i++)
		{
			// Release the elements in the array
			CTableEntity* pTable = (CTableEntity*)m_arrTable.GetAt(i);
			if (pTable != NULL)
			{
				delete pTable;
				pTable = NULL;
			}
		}

		// Empty array
		m_arrTable.RemoveAll();

		// Get table information
		tbLogic.GetTables(m_dbEntity.GetName(), m_arrTable);
	}
	catch(CAppException* e)
	{
		m_strError = e->GetErrorMessage();
		delete e;
	}
}

/*****************************************************
[FunctionName] GetTable
[Function]	Get a table in the table array,according to the index
[Argument]	int nIndex: Index of the table array
[ReturnedValue] CTableEntity*: Pointer to the table object
*****************************************************/
CTableEntity* CRKDBMSDoc::GetTable(int nIndex)
{
	return (CTableEntity*)m_arrTable.GetAt(nIndex);
}

/*****************************************************
[FunctionName] GetTableNum
[Function]	Get the number of the table
[Argument]	void
[ReturnedValue] int:The number of the table in the table information array
*****************************************************/
int CRKDBMSDoc::GetTableNum()
{
	return m_arrTable.GetCount();
}