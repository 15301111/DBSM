#include "stdafx.h"
#include "IndexLogic.h"
#include"FieldDAO.h"
#include"indexDAO.h"
#include"Util.h"

CIndexLogic::CIndexLogic(CString dbname, CString tableName)
{
	this->dbName = dbname;
	this->tbName = tableName;
	this->pkName = CString("");
	this->uniName = CString("");

	CString tdfPath = DEFAULT_ROOT + CString("/") + dbName + CString("/") + tbName + CString(".tdf");
	vector<CFieldEntity> fieldlist = CFieldDAO::ReadFieldList(tdfPath);
	for (vector<CFieldEntity>::iterator ite = fieldlist.begin();ite != fieldlist.end(); ite++) {
		if (ite->GetIsPK()) {
			pkName = ite->GetName();
			break;
		}
	}
	for (vector<CFieldEntity>::iterator ite = fieldlist.begin();ite != fieldlist.end(); ite++) {
		if (ite->GetIsUnique()) {
			uniName = ite->GetName();
			break;
		}
	}
}

CIndexLogic::~CIndexLogic(void)
{
}

bool CIndexLogic::sort(CRecordEntity &record) {
	//寻找主键
	
	vector<CRecordEntity> rds = CIndexDAO::readRd(this->dbName, this->tbName);

	//如果主键文件中没有记录
	if (rds.size() == 0) {
		rds.push_back(record);
		CIndexDAO::writeManyRd(this->dbName, this->tbName, rds);
		return FALSE;
	}
	
		if (this->pkName!=CString("")) {
			for (vector<CRecordEntity>::iterator ite = rds.begin(); ite != rds.end();++ite) {
				int a = CUtil::StringToInteger(record.GetValue(this->pkName));
				int b = CUtil::StringToInteger(ite->GetValue(this->pkName));
				if ( a<b ) {
					rds.insert(ite, record);
					break;
				}
				else {
					if (ite == (rds.end() - 1)) {
						rds.push_back(record);
						break;
					}
				}
			}
			CIndexDAO::writeManyRd(this->dbName, this->tbName, rds);
			
		}
	
	return TRUE;
}



