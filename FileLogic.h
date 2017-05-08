#pragma once


class CFileLogic
{
public:
	CString GetDBFile(void);
	CString GetDBFolder(const CString strDBName);

private:
	CString GetAbsolutePath(const CString strRelativePath);
};