#include "stdafx.h"
#include "indexDAO.h"
#include "RecordDAO.h"


bool CIndexDAO::InitIndFile(CString dbName, CString tableName)
{
	bool crtTdfFile;
	bool crtTrdile;
	CString path = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName;
	CString priPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName + CString("/") + CString("primary.ind");
	CString uniPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName + CString("/") + CString("uinque.ind");
	bool crtFolder = CUtil::CreateFolder(path);
	if (crtFolder) {
		vector<CString> init;
		init.push_back(CString("0#") + dbName + CString("#") + tableName);
		crtTdfFile = CBinaryFile::Write(priPath, init);
		crtTrdile = CBinaryFile::Write(uniPath, init);
	}

	return crtFolder&&crtTdfFile&&crtTrdile ;
}

void CIndexDAO::writeManyRd(CString dbName , CString tableName ,vector<CRecordEntity> records)
{
	CString path;
	
	path = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName + CString("/") + CString("primary.ind");
	CString tdfPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName + CString(".tdf");
	
	vector<CFieldEntity>fieldList = CFieldDAO::ReadFieldList(tdfPath);
	CRecordDAO::DeleteAllRecord(path);

	for (vector<CRecordEntity>::iterator ite0 = records.begin();ite0!=records.end();ite0++) {
		CString str = CUtil::IntegerToString(ite0->GetId());		
		for (vector<CFieldEntity>::iterator ite1 = fieldList.begin(); ite1 != fieldList.end(); ++ite1){
			str += CString("#") + ite0->GetValue(ite1->GetName());
		}		
		CBinaryFile::AddAnLine(path, str);
	}	
}

vector<CRecordEntity> CIndexDAO::readRd(CString dbName, CString tableName)
{
	vector<CRecordEntity> res;
	CString path;
	path = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName + CString("/") + CString("primary.ind");
	
	CString tdfPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tableName + CString(".tdf");
	vector<CFieldEntity>fieldList = CFieldDAO::ReadFieldList(tdfPath);

	res=CRecordDAO::ReadRecordList(path,fieldList);
	return res;
}


