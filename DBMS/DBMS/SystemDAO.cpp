#include "stdafx.h"
#include "SystemDAO.h"


CSystemDAO::CSystemDAO(void)
{
}


CSystemDAO::~CSystemDAO(void)
{
}


bool CSystemDAO::VerifyLogin(CString &username,CString &pwd,CString &fileName)
{
	vector<CString> list = CBinaryFile::ReadAll(fileName);
	bool isTrue = false;
	for (vector<CString>::iterator ite = list.begin(); ite != list.end(); ++ite)
	{
		vector<CString> temp = CUtil::StrSplit(*ite,L"#");
		if (temp[0]==username && temp[1] == pwd)
		{
			isTrue = true;
			break;
		}
	}

	return isTrue;
}

bool CSystemDAO::HasUserName(CString &username,CString &fileName)
{
	vector<CString> list = CBinaryFile::ReadAll(fileName);
	bool isTrue = false;
	for (vector<CString>::iterator ite = list.begin(); ite != list.end(); ++ite)
	{
		vector<CString> temp = CUtil::StrSplit(*ite,L"#");
		if (temp[0]==username)
		{
			isTrue = true;
			break;
		}
	}

	return isTrue;
}


bool CSystemDAO::Register(CString &username,CString &pwd,CString &fileName)
{
	if (this->HasUserName(username,fileName))
		return false;
	else
	{
		CString str = username + CString("#") + pwd;
		return CBinaryFile::AddAnLine(fileName,str);
	}
	
}

bool CSystemDAO::WriteLog(CString &info,CString &fileName)
{
	//return CBinaryFile::AddAnLine(fileName,info);
	
	info+="\r\n";

	CFile writefile;
	bool openWrite=writefile.Open(fileName,CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	if(openWrite){
		writefile.SeekToEnd();
		int num=info.GetLength()*2;
		writefile.Write(info,num);
		writefile.Close();
	}
	else
		return false;
	
	
	return true;

}

void CSystemDAO::LookLog(CString &fileName)
{
	ShellExecuteW(NULL, CString("open"), fileName, NULL, NULL, SW_SHOWNORMAL);
}


CString CSystemDAO::GetCurrUserName(CString &fileName)
{
	return CBinaryFile::ReadFirstLine(fileName);
}

bool CSystemDAO::SaveCurrUserName(CString &fileName,CString &username)
{
	vector<CString> strname;
	strname.push_back(username);
	return CBinaryFile::Write(fileName,strname);
}

bool CSystemDAO::SaveCurrPassword(CString &fileName,CString &password)
{
	vector<CString> strpassword;
	strpassword.push_back(password);
	return CBinaryFile::Write(fileName,strpassword);
}
