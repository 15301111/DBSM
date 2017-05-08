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
	CDBDao m_daoDB;			// ���ݿ����ݲ�������
	CFileLogic m_fileLogic;	// ���ݿ��ļ�����
};