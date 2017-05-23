#include "stdafx.h"
#include "DBLogic.h"
#include "DBDAO.h"
#include "Global.h"
#include "TableEntity.h"
#include "TableDAO.h"
#include "SystemLogic.h"

CDBLogic::CDBLogic(void)
{
	this->sysPath=DEFAULT_SYS_FILE;
}


CDBLogic::~CDBLogic(void)
{
}


vector<CDBEntity> CDBLogic::GetDatabaseList()
{
	vector<CDBEntity> list=CDBDAO::ReadDBList(sysPath);
	return list;
}

//����һ�����ݿ������������ݿ�
int CDBLogic::CreateDatabase(CString &dbName)
{
	vector<CDBEntity> dblist=CDBDAO::ReadDBList(sysPath);
	bool bExist=false;
	for (vector<CDBEntity>::iterator ite=dblist.begin();ite!=dblist.end();++ite)
	{
		if(ite->GetName()==dbName)
		{
			bExist=true;
			break;
		}
	}

	if (!bExist)
	{
		int counter=CDBDAO::ReadDBCounter(sysPath);
		CDBEntity db(++counter,dbName,DB_USER);
		//MessageBox(NULL,CUtil::IntegerToString(counter),L"",MB_OK);
		//��Ӽ�¼��ϵͳ�ļ�
		if(!CDBDAO::WriteAnDB(db,sysPath))
			return ADD_ERROR;
		
		//��ʼ��db�ļ�
		if(!CDBDAO::InitDBFile(dbName))
			return INITIATE_ERROR;
		
		if(!CDBDAO::SaveDBCounter(counter))
			return SAVE_COUNTER_ERROR;

		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("created database:")+dbName);

		return YES;
	}
	else
	{
		return DB_EXIST;
	}
}

//����һ�����ݿ����������ݿ�id���޸����ݿ�
int CDBLogic::ModifyDBName(CString &oldDBName,CString &newDBName)
{
	vector<CDBEntity> dblist=CDBDAO::ReadDBList(sysPath);
	bool bExist=false;
	for (vector<CDBEntity>::iterator ite=dblist.begin();ite!=dblist.end();++ite)
	{
		if(ite->GetName()==newDBName)
		{
			bExist=true;
			break;
		} 
	}

	if (bExist)
		return DB_EXIST;
	else
	{
		if(!CDBDAO::ModifyDBName(oldDBName,newDBName,DEFAULT_SYS_FILE)||
		   !CDBDAO::ModifyDirName(oldDBName,newDBName))
			return MODIFY_ERROR;
		else
		{

			CSystemLogic sysLogic;
			sysLogic.WriteLog(CString("modified database name,")+oldDBName+CString("->")+newDBName);
			return YES;
		}
			
	
	}
}

//ɾ��ָ�������ݿ�
int CDBLogic::DeleteDatabase(CString &dbname)
{
	if(!CDBDAO::DeleteDBRecord(this->sysPath,dbname)||!CDBDAO::DeleteDBFile(dbname))
		return DELETE_ERROR;
	else
	{
		CSystemLogic sysLogic;
		sysLogic.WriteLog(CString("deleted database:")+dbname);
		return YES;
	}
		
}


bool CDBLogic::BackupDatabase(CString &dbName,CString &destPath)
{
	CSystemLogic sysLogic;
	sysLogic.WriteLog(CString("backuped database:")+dbName);
	return CDBDAO::BackupDB(dbName,destPath);
}

bool CDBLogic::ImportDatabase(CString &path,CString &dbName)
{
	CSystemLogic sysLogic;
	sysLogic.WriteLog(CString("imported database:")+dbName);
	return CDBDAO::ImportDB(path,dbName);
}
