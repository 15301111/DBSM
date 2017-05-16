#pragma once
#include "Global.h"

class CSystemDAO
{
public:
	CSystemDAO(void);
	~CSystemDAO(void);

	bool VerifyLogin(CString &username,CString &pwd,CString &fileName);
	bool HasUserName(CString &username,CString &fileName);
	bool Register(CString &username,CString &pwd,CString &fileName);
	bool WriteLog(CString &info,CString &fileName);
	void LookLog(CString &fileName);
	CString GetCurrUserName(CString &fileName);
	bool SaveCurrUserName(CString &fileName,CString &username);
};

