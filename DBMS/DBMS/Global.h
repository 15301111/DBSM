#pragma once

#define STRING_LENGTH 1024	//�ַ�������
#define INVALID	0			//��Ҫ����id�Ĳ��Ϸ���
#define YES 1				//
#define NO 0				//


#define OPERATE_ADD 1		//���Ӳ���
#define OPERATE_MODIFY 2	//�޸Ĳ���

#define DB_SYSTEM 1			//ϵͳ���ݿ�
#define DB_USER 2			//�û����ݿ�

#define DB_INTEGER 1			//���ͣ���Ӧint
#define DB_BOOL 2				//����ֵ���ͣ���Ӧbool
#define DB_DOUBLE 3				//˫�����ͣ���Ӧdouble
#define DB_VARCHAR 4			//�ɱ䳤�ַ����ͣ���ӦCString
#define DB_DATETIME 5			//ʱ�����ͣ���ӦSYSTEMTIME

#define DEFAULT_FIELD_LENGTH 20	//Ĭ���ֶγ���
#define DEFAULT_PAGE_RECORDNUM 20 //Ĭ��ÿҳ��ʾ��Ŀ

#define DEFAULT_SYS_FILE CString("data/dbms.sys") //Ĭ�ϵ�ϵͳ�ļ�����
#define DEFAULT_ROOT CString("data")			//Ĭ�����ݸ�Ŀ¼

//������Լ��
#define INTEGRITY_OK 300	//����
#define INTEGRITY_OVER_RANGE 301 //������Χ
#define INTEGRITY_TOO_LONG 302 //�ַ�����
#define INTEGRITY_ERROR_CHAR 303 //�����ַ�
#define INTEGRITY_NULL_VALUE 304//�ֶο�ֵ
#define INTEGRITY_NOT_UNIQUE 305//�ֶβ�Ψһ
#define INTEGRITY_NOT_PK 306//����������Լ��
#define INTEGRITY_ERROR_TYPE 350//��������
#define INTEGRITY_ERROR_DATETYPE 351//������������

//�߼���
#define DB_EXIST 307			//���ݿ��Ѵ���
#define DB_NOT_EXIST 308		//���ݿⲻ����
#define FIELD_EXIST 309			//�ֶ��Ѵ���
#define FIELD_NOT_EXIST 310		//�ֶβ�����
#define RECORD_NOT_EXIST 311	//��¼������
#define TABLE_EXIST 312			//���Ѵ���
#define TABLE_NOT_EXIST 313		//������

#define INITIATE_ERROR 314		//��ʼ������
#define ADD_ERROR 315			//��Ӵ���
#define MODIFY_ERROR 316		//�޸Ĵ���
#define DELETE_ERROR 317		//ɾ������
#define SAVE_COUNTER_ERROR 318  //�������������


#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
#include "Util.h"	//������
#include "BinaryFile.h"	//�ļ�������


class Varchar
{
private:
	CString value;
public:
	Varchar(CString val):value(val){}
	int GetLength() { return value.GetLength(); };
	CString GetValue() { return value; };
};