#include "StdAfx.h"
#include "FileLogic.h"

//得到数据库描述文件

CString CFileLogic::GetDBFile(void)
{
	CString strPath = _T("");
	try
	{
		// Get absolute path of ruanko.db file
		strPath = GetAbsolutePath(_T("mydbms.db"));
	}
	catch (CAppException* e)
	{
		throw e;
	}
	return strPath;
}


CString CFileLogic::GetDBFolder(const CString strDBName)
{
	CString strFolder = _T("");
	try
	{
		// Get the path of the database folder
		strFolder.Format(_T("data\\%s"), strDBName);
		strFolder = GetAbsolutePath(strFolder);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("打开数据库文件路径失败!"));
	}

	return strFolder;
}

CString CFileLogic::GetAbsolutePath(const CString strRelativePath)
{
	CString strFolder = _T("");
	try
	{
		
		wchar_t acExeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, acExeFullPath, MAX_PATH);
		CString strFolder = acExeFullPath;
		int pos = strFolder.ReverseFind('\\');
		strFolder = strFolder.Left(pos+1);
		return strFolder + strRelativePath;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("打开文件路径失败!"));
	}
	catch (...)
	{
		throw new CAppException(_T("打开文件路径失败!"));
	}

	return strFolder;
}