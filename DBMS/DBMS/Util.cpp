#include "stdafx.h"
#include "Util.h"
#include "Global.h"


CUtil::CUtil(void)
{
}


CUtil::~CUtil(void)
{
}




/****************************************
* 把一个字符串按照分隔符分成字符串数组的形式
****************************************/
vector<CString> CUtil::StrSplit(CString str,CString split)
{
	vector<CString> res;
	string::size_type index=0;
	str+=split;
	while(str.GetLength()!=0)
	{
		index=str.Find(split);
		res.push_back(str.Left(index));
		str.Delete(0,index+1);
	}
	return res;
}

/****************************************
* 获取当前系统时间
****************************************/
CString CUtil::GetCurrTime()
{
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CTime t(time);
	return t.Format("%Y-%m-%d %H:%M:%S");
}

/****************************************
* char*转化成String
****************************************/
CString CUtil::CharArrToString(char *charArr)
{
	return charArr==NULL?NULL:CString(charArr);
}

/****************************************
* String转化成char *
****************************************/
char *CUtil::StringToCharArr(CString cstring)
{
	if (cstring)
	{
		//针对Unicode编码的转化方案
		USES_CONVERSION;
		return T2A(cstring);

		//int le=cstring.GetLength()+1;
		//char *res=new char[le];
		//strncpy_s(res,cstring,le);
		//return res;

		//char *res=(_bstr_t)cstring.allocsysstring();
		//return res;

	}
	else
	{
		return NULL;
	}
}


/****************************************
* 数字转化成字符串
****************************************/
CString CUtil::IntegerToString(int number)
{
	if(number==NULL)
		return CString("0");
	else
	{
		char buff[STRING_LENGTH];
		sprintf_s(buff,"%d",number);
		return CString(buff);
	}
}

/****************************************
* 字符串转化成数字
****************************************/
int CUtil::StringToInteger(CString cstring)
{
	if(!cstring)
		return NULL;

	return atoi(StringToCharArr(cstring));
}


int CUtil::StringToBool(CString cstring)
{
	if (cstring==CString("TRUE"))
	{
		return YES;
	}
	else
	{
		return NO;
	}
}


CString CUtil::BoolToString(int b)
{
	if (b==1)
	{
		return CString("TRUE");
	}
	else
	{
		return CString("FALSE");
	}
}


double CUtil::StringToDouble(CString cstring)
{
	if(cstring)
		return atof(CUtil::StringToCharArr(cstring));
	else
		return 0;
}

CString CUtil::DoubleToString(double doubleNum)
{
	if(doubleNum==NULL)
		return CString("0");
	else
	{
		char buff[STRING_LENGTH];
		sprintf_s(buff,"%lf",doubleNum);
		return CString(buff);
	}
}







/****************************************
* 删除文件夹
****************************************/
bool CUtil::DeleteFolder(CString &folderName)
{

	CFileFind finder;
	CString path;
	path.Format(CString("%s/*.*"),folderName);
	BOOL bWorking = finder.FindFile(path);
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory() && !finder.IsDots())
		{//处理文件夹
			DeleteFolder(finder.GetFilePath()); //递归删除文件夹
			RemoveDirectory(finder.GetFilePath());
		}
		else
		{//处理文件
			DeleteFile(finder.GetFilePath());
		}
	}
	if(!RemoveDirectory(folderName))
		return false;

    return true;
}

/****************************************
* 创建文件夹
****************************************/
bool CUtil::CreateFolder(CString &folderName)
{
	return CreateDirectory(folderName,NULL)!=0;
}

/****************************************
* 修改文件夹名称
****************************************/
bool CUtil::ModifyFolderName(CString &oldname,CString &newname)
{
	return MoveFile(oldname,newname)!=0;
}

/****************************************
* 修改文件名称
****************************************/
bool CUtil::ModifyFileName(CString &oldname,CString &newname)
{
	try
	{
		CFile::Rename(oldname,newname);
	}
	catch (CFileException* pEx)
	{
		MessageBox(NULL,CString("修改失败：")+pEx->m_strFileName,CString("修改文件名称"),MB_OK);
		return false;
	}

	return true;
}

bool CUtil::DeleteFileA(CString &filename)
{
	return DeleteFile(filename)!=0;
}

CString CUtil::GetError(int code)
{
	CString res("未知错误！");
	switch (code)
	{
	case INTEGRITY_OVER_RANGE:res=CString("错误：数据超出范围！");break;
	case INTEGRITY_TOO_LONG:res=CString("错误：字段过长！");break;
	case INTEGRITY_ERROR_CHAR:res=CString("错误：出现错误字符！");break;
	case INTEGRITY_NULL_VALUE:res=CString("错误：出现字段为空！");break;
	case INTEGRITY_NOT_UNIQUE:res=CString("错误：不符合唯一性约束！");break;
	case INTEGRITY_NOT_PK:res=CString("错误：不符合主键约束！");break;
	case INTEGRITY_ERROR_TYPE:res=CString("错误：出现错误的数据类型！");break;
	case DB_EXIST:res=CString("错误：数据库已存在！");break;
	case DB_NOT_EXIST:res=CString("错误：数据库不存在！");break;
	case FIELD_EXIST:res=CString("错误：字段已存在！");break;
	case FIELD_NOT_EXIST:res=CString("错误：字段不存在！");break;
	case RECORD_NOT_EXIST:res=CString("错误：记录不存在！");break;
	case TABLE_EXIST:res=CString("错误：表已存在！");break;
	case TABLE_NOT_EXIST:res=CString("错误：表不存在！");break;
	case INITIATE_ERROR:res=CString("错误：初始化错误！");break;
	case ADD_ERROR:res=CString("错误：增加出错！");break;
	case MODIFY_ERROR:res=CString("错误：修改出错！");break;
	case DELETE_ERROR:res=CString("错误：删除出错！");break;
	case SAVE_COUNTER_ERROR:res=CString("错误：保存计数器出错！");break;
	case INTEGRITY_ERROR_DATETYPE:res=CString("错误：错误的日期类型！");break;

	default:
		break;
	}
	return res;
}


CString CUtil::GetIcon(int flag)
{
	if(flag==1)
		return CString("√");
	else
		return CString("");
}

int CUtil::IconToInt(CString icon)
{
	if(icon==L"√")
		return 1;
	else
		return 0;
}


CString CUtil::GetDataType(int type)
{
	switch (type)
	{
	case DB_INTEGER:
		return CString("Integer");
	case DB_BOOL:
		return CString("Bool");
	case DB_DATETIME:
		return CString("DataTime");
	case DB_DOUBLE:
		return CString("Double");
	case DB_VARCHAR:
		return CString("Varchar");
	default:
		break;
	}
	return CString("未知");
}

int CUtil::TypeToInt(CString type)
{

	if(type=="Integer")
	{
		return DB_INTEGER;
	}
	else if(type=="Bool")
	{
		return DB_BOOL;
	}
	else if(type=="Double")
	{
		return DB_DOUBLE;
	}
	else if(type=="Varchar")
	{
		return DB_VARCHAR;
	}
	else if(type=="DataTime")
	{
		return DB_DATETIME;
	}
	else
		return 0;
}


bool CUtil::OnlyHaveNumber(CString &str)
{
	bool isOK =true;
	if (str != str.SpanIncluding(L"1234567890"))
		isOK = false;
	return isOK;
}

bool CUtil::OnlyHaveNumberAndDot(CString &str)
{
	bool isOK =true;
	if (str != str.SpanIncluding(L"1234567890."))
		isOK = false;
	return isOK;
}

bool CUtil::ValidStr(CString &str)
{
	bool isOK =true;
	if (str != str.SpanExcluding(L"!@#$%^&*()_+-={}[]:\";'<>?/"))
		isOK = false;
	return isOK;
}

//复制文件夹里的内容
void CUtil::CopyDirectory(CString source, CString target)  
{  
    CreateDirectory(target,NULL); //创建目标文件夹   
    //AfxMessageBox("创建文件夹"+target);   
    CFileFind finder;  
    CString path;  
    path.Format(L"%s/*.*",source);   
    bool bWorking = finder.FindFile(path);  
    while(bWorking)
	{  
        bWorking = finder.FindNextFile();  
        if(finder.IsDirectory() && !finder.IsDots())
		{ //是文件夹 而且 名称不含 . 或 ..   
            CopyDirectory(finder.GetFilePath(),target+"/"+finder.GetFileName()); //递归创建文件夹+"/"+finder.GetFileName()   
        }
        else
		{ //是文件 则直接复制    
            CopyFile(finder.GetFilePath(),target+"/"+finder.GetFileName(),FALSE);  
        }  
    }
}