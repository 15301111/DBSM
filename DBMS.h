
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       

// CDBMSApp:
// �йش����ʵ�֣������ DBMS.cpp
//

class CRKDBMSApp : public CWinApp
{
public:
	CRKDBMSApp();



public:
	virtual BOOL InitInstance();   
	virtual int ExitInstance();   
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRKDBMSApp theApp;
