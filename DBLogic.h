#pragma once
#include "DBEntity.h"
#include "DBDao.h"
#include "FileLogic.h"


class CDBLogic
{
public:
	
	bool CreateDatabase(CDBEntity &db);

	bool GetDatabase(CDBEntity &db);

private:
	CDBDao m_daoDB;			// 数据库数据操作对象
	CFileLogic m_fileLogic;	// 数据库文件对象
};