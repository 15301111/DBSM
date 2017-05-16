#include "stdafx.h"
#include "DBDAO.h"
#include "BinaryFile.h"
#include "Global.h"


CDBDAO::CDBDAO(void)
{
}


CDBDAO::~CDBDAO(void)
{
}

//���ļ���ȡ���ݿ��б�
vector<CDBEntity> CDBDAO::ReadDBList(CString &sysFileName)
{
	vector<CDBEntity> res;
	vector<CString> strList=CBinaryFile::ReadAll(sysFileName);
	//MessageBox(NULL,CUtil::IntegerToString(strList.size()),L"",MB_OK);
	if(!strList.empty())
	{
		vector<CString>::iterator ite=strList.begin();
		++ite;
		for(;ite!=strList.end();++ite)
		{
			res.push_back(CDBEntity(*ite));
		}
	}

	return res;
}

//��ȡ���ݿ�ļ�����
int CDBDAO::ReadDBCounter(CString &sysFileName)
{
	CString tmp=CBinaryFile::ReadFirstLine(sysFileName);
	int counter=CUtil::StringToInteger(CBinaryFile::ReadFirstLine(sysFileName));
	return counter;
}

//����һ�����ݿ⵽�ļ�
bool CDBDAO::WriteAnDB(CDBEntity &newDB,CString &sysFileName)
{
	CString str=CUtil::IntegerToString(newDB.GetId())+CString("#")+newDB.GetName()+CString("#")+CUtil::IntegerToString(newDB.GetType())+CString("#")+CUtil::IntegerToString(newDB.GetTableNum())+CString("#")+newDB.GetCreateTime();
	return(CBinaryFile::AddAnLine(sysFileName,str));
}

//���е����ݿ���д�����ݿ�
bool CDBDAO::ModifyDBName(CString &oldName,CString &newName,CString &sysFileName)
{
	vector<CString> strList = CBinaryFile::ReadAll(sysFileName);
	if(!strList.empty())
	{
		for(vector<CString>::iterator ite=strList.begin()+1;ite!=strList.end();++ite)
		{
			vector<CString> tmpList=CUtil::StrSplit(*ite,L"#");
			if(tmpList[1]==oldName)
			{
				tmpList[1]= newName;
				*ite=tmpList[0]+CString("#")+
					tmpList[1]+CString("#")+
					tmpList[2]+CString("#")+
					tmpList[3]+CString("#")+
					tmpList[4];
				break;
			}
		}
	}
	return CBinaryFile::Write(sysFileName,strList);
}

//ɾ��ϵͳ�ļ������ݿ�ļ�¼
bool CDBDAO::DeleteDBRecord(CString &sysFileName,CString &dbname)
{
	vector<CString> list=CBinaryFile::ReadAll(sysFileName);
	if(list.empty())
		return false;
	else
	{
		vector<CString>::iterator ite=list.begin();
		++ite;
		for (; ite!=list.end(); ++ite)
		{
			vector<CString> temp = CUtil::StrSplit(*ite,CString("#"));
			//����ҵ�ָ���ļ�¼
			if (temp[1] == dbname)
			{
				list.erase(ite);
				break;
			}
		}
		if (CBinaryFile::Write(sysFileName,list))
			return true;
		else
			return false;
	}
	
}


//�������ݿ���ɾ�����ڸ����ݿ��ȫ���ļ�
bool CDBDAO::DeleteDBFile(CString &dbName)
{
	return (CUtil::DeleteFolder(DEFAULT_ROOT+CString("/")+dbName));
}

bool CDBDAO::InitDBFile(CString &dbName)
{
	CString folderPath = DEFAULT_ROOT+CString("/")+dbName;
	CString dbPath = folderPath + CString("/") + dbName + CString(".db");
	bool crtFolder = CUtil::CreateFolder(folderPath);
	vector<CString> init;
	init.push_back(CString("0#")+dbName);
	bool crtDBFile = CBinaryFile::Write(dbPath,init);

	return crtFolder&&crtDBFile;
}

bool CDBDAO::ModifyDirName(CString &oldName,CString &newName)
{
	CString oldDBFileName = DEFAULT_ROOT + "/" + oldName+"/"+oldName+".db";
	CString newDBFileName = DEFAULT_ROOT + "/" + oldName+"/"+newName+".db";
	vector<CString> strList = CBinaryFile::ReadAll(oldDBFileName);
	if(!strList.empty())
	{
		//vector<CString>::iterator ite=strList.begin();
		CString first = strList[0];
		vector<CString> temp = CUtil::StrSplit(first,CString("#"));
		temp[1]=newName;
		first=temp[0]+CString("#")+temp[1];
		strList[0]=first;
	}
	if(CBinaryFile::Write(oldDBFileName,strList)&&
		CUtil::ModifyFileName(oldDBFileName,newDBFileName)&&
		CUtil::ModifyFolderName(DEFAULT_ROOT + L"/" + oldName, DEFAULT_ROOT + L"/" + newName))
		return true;
	else
		return false;
	
}

bool CDBDAO::SaveDBCounter(int counter)
{
	vector<CString> list = CBinaryFile::ReadAll(DEFAULT_SYS_FILE);
	if(list.empty())
		return false;
	else
	{
		list[0] = CUtil::IntegerToString(counter);
		if(CBinaryFile::Write(DEFAULT_SYS_FILE,list))
			return true;
		else
			return false;
	}
	
}



bool CDBDAO::BackupDB(CString &dbName,CString &destPath)
{
	CString dbPath = DEFAULT_ROOT + CString("/") + dbName;
	CUtil::CopyDirectory(dbPath,destPath);
	//�����ļ����Ƶ�db.back
	vector<CString> str;
	str.push_back(dbName+L".db");
	return CBinaryFile::Write(destPath+L"/db.back",str);
}

bool CDBDAO::ImportDB(CString &sourcePath,CString &destDBName)
{
	CString destPath = DEFAULT_ROOT + CString("/") + destDBName;
	CUtil::CopyDirectory(sourcePath,destPath);
	CString fileName = destPath+CString("/")+CBinaryFile::ReadFirstLine(destPath+L"/db.back");
	vector<CString> list = CBinaryFile::ReadAll(fileName);
	bool writeSucc = CBinaryFile::Write(destPath+CString("/")+destDBName+CString(".db"),list);
	if(writeSucc)
	{
		CUtil::DeleteFileA(destPath+L"/db.back");
		CUtil::DeleteFileA(fileName);
		return true;
	}
	else
		return false;
	
	
}
