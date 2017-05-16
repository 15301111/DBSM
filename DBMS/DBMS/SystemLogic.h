#pragma once
class CSystemLogic
{
public:
	CSystemLogic(void);
	~CSystemLogic(void);

	bool VerifyLogin(CString &username,CString &pwd);
	bool Register(CString &username,CString &pwd);
	bool WriteLog(CString &oper);
	void LookLog();
};

