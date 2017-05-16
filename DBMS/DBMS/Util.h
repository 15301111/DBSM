#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

class CUtil
{
public:
	CUtil(void);
	~CUtil(void);


	static vector<CString> StrSplit(CString str,CString split);//�ַ����ָ��
	static CString GetCurrTime();							  //�õ���ǰʱ��
	static CString GetError(int code);						//ͨ��������õ�������Ϣ
	static CString GetIcon(int flag);						//���ݱ�־�õ��ǡ��̡����ǡ���
	static int IconToInt(CString icon);
	static CString GetDataType(int type);					//�õ��������ʹ����Ӧ����������
	static int TypeToInt(CString type);
	static CString CharArrToString(char *charArr);			//char*ת����CString
	static char *StringToCharArr(CString cstring);			//CStringת����char*

	static CString IntegerToString(int number);				//intת�����ַ���
	static int StringToInteger(CString cstring);			//�ַ���ת����int

	static int StringToBool(CString cstring);
	static CString BoolToString(int b);

	static double StringToDouble(CString cstring);
	static CString DoubleToString(double doubleNum);

	//static CString VarcharToString(Varchar var);
	//static Varchar StringToVarchar(CString cstring);



	//�ļ����ļ��в���
	static bool CreateFolder(CString &folderName);			//�����ļ���
	static bool ModifyFolderName(CString &oldname,CString &newname);//�޸��ļ�������
	static bool ModifyFileName(CString &oldname,CString &newname);	//�޸��ļ���
	static bool DeleteFolder(CString &folderName);			//ɾ���ļ���
	static bool DeleteFileA(CString &filename);				//ɾ���ļ�
	static void CopyDirectory(CString source, CString target);//�����ļ����������


	static bool OnlyHaveNumber(CString &str);		//�ַ����Ƿ�ֻ��������
	static bool OnlyHaveNumberAndDot(CString &str);	//�ַ����Ƿ�ֻ�������ֺ�"."
	static bool ValidStr(CString &str);		//�ַ����Ƿ�ֻ������ĸ�����ֺ�"_"
};
