#include "StdAfx.h"
#include "DBDao.h"


bool CDBDao::Create(const CString strFilepath, CDBEntity db, bool bAppend)
{
	try
	{
		CFile file;
		if(bAppend == true)
		{
			if (file.Open(strFilepath, CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			{
				return false;
			}
		}
		else
		{
			if (file.Open(strFilepath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite) == FALSE)
			{
				return false;
			}
		}

		file.SeekToBegin();
		file.Write(&db.GetBlock(), sizeof(DatabaseBlock));
		file.Close();

		return true;
	}
	catch(CException* e)
	{
		
		e->Delete();
	
		throw new CAppException(_T("Failed to create the database file!"));
	}
	catch(...)	
	{
		throw new CAppException(_T("Failed to create the database file!"));
	}

	return false;
}

bool CDBDao::GetDatabase(const CString strFilepath, CDBEntity &db)
{
	try
	{
		
		CString strDBName = db.GetName();
		if (strDBName.GetLength() == 0)
		{
			return false;
		}
		
		
		CFile file;
		if (file.Open(strFilepath, CFile::modeRead | CFile::shareDenyNone) == FALSE)
		{
			return false;
		}

		
		bool bExist = false;
		DatabaseBlock sdb;

		file.SeekToBegin();
		while (file.Read(&sdb, sizeof(DatabaseBlock)) > 0)
		{
			CString strName = CCharHelper::ToString(sdb.name, sizeof(VARCHAR));
			if (strName.CompareNoCase(strDBName) == 0)
			{
				db.SetBlock(sdb);
				bExist = true;
				break;
			}
		}
		file.Close();

		return bExist;
	}
	catch(CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to create the database file!"));
	}
	catch(...)	
	{
		throw new CAppException(_T("Failed to create the database file!"));
	}
	return false;
}



bool CDBDao::CreateFile(const CString strFileName)
{
	try
	{
		for (int i = 0; i < strFileName.GetLength(); i++)
		{
			if ( (_T('\\') == strFileName.GetAt(i)
				|| _T('/') == strFileName.GetAt(i))
				&& 2 != i
				)
			{
				CString strDirectory;
				strDirectory = strFileName.Left(i);
				if(!CreateDirectory(strDirectory, NULL) && 183 != GetLastError())
				{
					return false;
				}
			}
		}

		CFile file;
		if (!file.Open(strFileName, CFile::modeCreate))
		{
			return false;
		}
		file.Close();

		return true;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to create file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to create file!"));
	}

	return false;
}


bool CDBDao::IsValidFile(const CString strPath)
{
	try
	{
		CFile file;
		if (file.Open(strPath, CFile::modeRead | CFile::shareDenyNone) == TRUE)
		{
			file.Close();
			return true;
		}
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to open file"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to open file"));
	}
	return false;
}