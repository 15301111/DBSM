#include "stdafx.h"
#include "SystemLogic.h"
#include "SystemDAO.h"

CSystemLogic::CSystemLogic(void)
{
}


CSystemLogic::~CSystemLogic(void)
{
}

bool CSystemLogic::VerifyLogin(CString &username,CString &pwd)
{
	CSystemDAO sysDao;
	return sysDao.VerifyLogin(username,pwd,CString("sys/user.sys"));
	
}

bool CSystemLogic::Register(CString &username,CString &pwd)
{
	CSystemDAO sysDao;
	return sysDao.Register(username,pwd,CString("sys/user.sys"));
}

bool CSystemLogic::WriteLog(CString &oper)
{
	CString info("");
	CSystemDAO sysDao;
	info += sysDao.GetCurrUserName(CString("log/u.temp"));
	info += CString("  ") + oper;
	info += CString("  ") + CUtil::GetCurrTime();
	return sysDao.WriteLog(info,CString("log/sys.log"));
}

void CSystemLogic::LookLog()
{
	wchar_t path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);
	CString strPath(path);
	strPath += CString("\\log\\sys.log");
	CSystemDAO sysDao;
	sysDao.LookLog(strPath);
}
