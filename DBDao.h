#pragma once
#include "DBEntity.h"


class CDBDao
{
public:
	
	bool Create(const CString strFilepath, CDBEntity db, bool bAppend = true);
	bool GetDatabase(const CString strFilepath, CDBEntity &db);
	bool CreateFile(const CString strFileName);
	bool IsValidFile(const CString strPath);
};