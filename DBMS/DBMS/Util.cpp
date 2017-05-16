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
* ��һ���ַ������շָ����ֳ��ַ����������ʽ
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
* ��ȡ��ǰϵͳʱ��
****************************************/
CString CUtil::GetCurrTime()
{
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CTime t(time);
	return t.Format("%Y-%m-%d %H:%M:%S");
}

/****************************************
* char*ת����String
****************************************/
CString CUtil::CharArrToString(char *charArr)
{
	return charArr==NULL?NULL:CString(charArr);
}

/****************************************
* Stringת����char *
****************************************/
char *CUtil::StringToCharArr(CString cstring)
{
	if (cstring)
	{
		//���Unicode�����ת������
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
* ����ת�����ַ���
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
* �ַ���ת��������
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
* ɾ���ļ���
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
		{//�����ļ���
			DeleteFolder(finder.GetFilePath()); //�ݹ�ɾ���ļ���
			RemoveDirectory(finder.GetFilePath());
		}
		else
		{//�����ļ�
			DeleteFile(finder.GetFilePath());
		}
	}
	if(!RemoveDirectory(folderName))
		return false;

    return true;
}

/****************************************
* �����ļ���
****************************************/
bool CUtil::CreateFolder(CString &folderName)
{
	return CreateDirectory(folderName,NULL)!=0;
}

/****************************************
* �޸��ļ�������
****************************************/
bool CUtil::ModifyFolderName(CString &oldname,CString &newname)
{
	return MoveFile(oldname,newname)!=0;
}

/****************************************
* �޸��ļ�����
****************************************/
bool CUtil::ModifyFileName(CString &oldname,CString &newname)
{
	try
	{
		CFile::Rename(oldname,newname);
	}
	catch (CFileException* pEx)
	{
		MessageBox(NULL,CString("�޸�ʧ�ܣ�")+pEx->m_strFileName,CString("�޸��ļ�����"),MB_OK);
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
	CString res("δ֪����");
	switch (code)
	{
	case INTEGRITY_OVER_RANGE:res=CString("�������ݳ�����Χ��");break;
	case INTEGRITY_TOO_LONG:res=CString("�����ֶι�����");break;
	case INTEGRITY_ERROR_CHAR:res=CString("���󣺳��ִ����ַ���");break;
	case INTEGRITY_NULL_VALUE:res=CString("���󣺳����ֶ�Ϊ�գ�");break;
	case INTEGRITY_NOT_UNIQUE:res=CString("���󣺲�����Ψһ��Լ����");break;
	case INTEGRITY_NOT_PK:res=CString("���󣺲���������Լ����");break;
	case INTEGRITY_ERROR_TYPE:res=CString("���󣺳��ִ�����������ͣ�");break;
	case DB_EXIST:res=CString("�������ݿ��Ѵ��ڣ�");break;
	case DB_NOT_EXIST:res=CString("�������ݿⲻ���ڣ�");break;
	case FIELD_EXIST:res=CString("�����ֶ��Ѵ��ڣ�");break;
	case FIELD_NOT_EXIST:res=CString("�����ֶβ����ڣ�");break;
	case RECORD_NOT_EXIST:res=CString("���󣺼�¼�����ڣ�");break;
	case TABLE_EXIST:res=CString("���󣺱��Ѵ��ڣ�");break;
	case TABLE_NOT_EXIST:res=CString("���󣺱����ڣ�");break;
	case INITIATE_ERROR:res=CString("���󣺳�ʼ������");break;
	case ADD_ERROR:res=CString("�������ӳ���");break;
	case MODIFY_ERROR:res=CString("�����޸ĳ���");break;
	case DELETE_ERROR:res=CString("����ɾ������");break;
	case SAVE_COUNTER_ERROR:res=CString("���󣺱������������");break;
	case INTEGRITY_ERROR_DATETYPE:res=CString("���󣺴�����������ͣ�");break;

	default:
		break;
	}
	return res;
}


CString CUtil::GetIcon(int flag)
{
	if(flag==1)
		return CString("��");
	else
		return CString("");
}

int CUtil::IconToInt(CString icon)
{
	if(icon==L"��")
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
	return CString("δ֪");
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

//�����ļ����������
void CUtil::CopyDirectory(CString source, CString target)  
{  
    CreateDirectory(target,NULL); //����Ŀ���ļ���   
    //AfxMessageBox("�����ļ���"+target);   
    CFileFind finder;  
    CString path;  
    path.Format(L"%s/*.*",source);   
    bool bWorking = finder.FindFile(path);  
    while(bWorking)
	{  
        bWorking = finder.FindNextFile();  
        if(finder.IsDirectory() && !finder.IsDots())
		{ //���ļ��� ���� ���Ʋ��� . �� ..   
            CopyDirectory(finder.GetFilePath(),target+"/"+finder.GetFileName()); //�ݹ鴴���ļ���+"/"+finder.GetFileName()   
        }
        else
		{ //���ļ� ��ֱ�Ӹ���    
            CopyFile(finder.GetFilePath(),target+"/"+finder.GetFileName(),FALSE);  
        }  
    }
}