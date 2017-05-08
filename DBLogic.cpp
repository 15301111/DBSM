#include "StdAfx.h"
#include "DBLogic.h"


bool CDBLogic::CreateDatabase(CDBEntity &db)
{
	try 
	{
		
		CString strDBFile = m_fileLogic.GetDBFile();
		if (m_daoDB.IsValidFile(strDBFile) == false)
		{
			if(m_daoDB.CreateFile(strDBFile) == false)
			{
				return false;
			}
		}


		if (m_daoDB.GetDatabase(strDBFile, db) == true)
		{
			return false;
		}

		CString strDBFolder = m_fileLogic.GetDBFolder(db.GetName());
		db.SetFilepath(strDBFolder);
		if(m_daoDB.Create(strDBFile, db) == false)
		{
			return false;
		}
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("创建数据库失败"));
	}

	return true;
}


bool CDBLogic::GetDatabase(CDBEntity &db)
{
	try
	{
		return m_daoDB.GetDatabase(m_fileLogic.GetDBFile(), db);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("创建数据库失败"));
	}
	return false;
}