#include "stdafx.h"
#include<iostream>
#include<fstream>
#include "BinaryFile.h"


CBinaryFile::CBinaryFile(void)
{
}


CBinaryFile::~CBinaryFile(void)
{
}

//分条读取全部文件的内容
vector<CString> CBinaryFile::ReadAll(CString &fileName){
	vector<CString> res;
	long count=0;
	TCHAR con[256];
	ZeroMemory(con,sizeof(con));
	char len[4];
	CFile readfile;
	bool openRead=readfile.Open(fileName,CFile::modeRead|CFile::typeBinary);
	if(openRead){
		
		while(readfile.Read(len,4)!=0){
			long num=atoi(len);
			readfile.Read(con,num);
			CString temp = con;
			ZeroMemory(con, sizeof(con));
			res.push_back(temp);
		}
		readfile.Close();
	}
	else
	{
		MessageBox(NULL,CString("打开文件失败！"),CString("错误"),MB_OK | MB_ICONWARNING);
	}
	
	return res;

}

//读取指定页的文件的内容
vector<CString> CBinaryFile::Read(CString &fileName,int pageNo,int pageRcdNo){
	vector<CString> res;
	CString temp;
	TCHAR con[256];
	ZeroMemory(con,sizeof(con));
	char len[4];
	CFile readfile;
	bool openRead=readfile.Open(fileName,CFile::modeRead|CFile::typeBinary);
	if(openRead){

		for(int j=0;j<pageNo;j++){
			for(int k=0;k<pageRcdNo;k++){
				readfile.Read(len,4);
				int temp_num=atoi(len);
				readfile.Seek(temp_num,CFile::current);
			}
		}
		
		for(int i=0;i<pageRcdNo;i++){
			readfile.Read(len,4);
			int num=atoi(len);
			readfile.Read(con,num);
			
			res.push_back(temp);
		}
		readfile.Close();
	}
	else
	{
		MessageBox(NULL,CString("打开文件失败！"),CString("错误"),MB_OK | MB_ICONWARNING);
	}
	
	return res;

}

//读取第一条文件的内容
CString CBinaryFile::ReadFirstLine(CString &fileName){
	CString res("");
	TCHAR con[256];
	ZeroMemory(con,sizeof(con));
	char len[4];
	CFile readfile;
	bool openRead=readfile.Open(fileName,CFile::modeRead|CFile::typeBinary);
	if(openRead){

		readfile.Read(len,4);
		int num=atoi(len);
		readfile.Read(con,num);
		res = CString(con);
		readfile.Close();	
	}
	return res;
}

//将多条记录一次性写入文件
bool CBinaryFile::Write(CString &fileName,vector<CString> &str){
	bool res = true;
	CFile writefile;
	bool openWrite=writefile.Open(fileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary/*|CFile::modeNoTruncate*/);
	if(openWrite){
		//writefile.SeekToEnd();
		for(int i=0;i < str.size();i++){
			int num=str[i].GetLength()*2;
			char len[4];
			ZeroMemory(len, sizeof(len));
			sprintf_s(len,"%d",num);
			writefile.Write(len,4);
			writefile.Write(str[i],num);
		}
		writefile.Close();
	}
	else
	{
		res = false;
	}
	
	return res;
}


//在文件末尾加入一条记录
bool CBinaryFile::AddAnLine(CString &fileName,CString &str){
	CFile writefile;
	bool openWrite=writefile.Open(fileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary|CFile::modeNoTruncate);
	if(openWrite){
		writefile.SeekToEnd();
		int num=str.GetLength()*2;
		char len[4];
		ZeroMemory(len, sizeof(len));
		sprintf_s(len,"%d",num);
		writefile.Write(len,4);
		writefile.Write(str,num);
		writefile.Close();
	}
	else
	{
		return false;
	}
	
	return true;
}
 
bool CBinaryFile::DeleteRecordByName(CString &fileName,CString &name){
	vector<CString> res=CBinaryFile::ReadAll(fileName);
	vector<CString> splitedString;
	CString split=CString('#');
	int  i = -1;
	do{
		i++;
		splitedString=CUtil::StrSplit(res[i],split);

	}while(splitedString[1]!=name);

	for(i=i+1;i<res.size();i++){
		res[i-1]=res[i];
	}
	res.pop_back();

	CFile remove;
	remove.Remove(fileName);

	bool judge;
	judge=CBinaryFile::Write(fileName,res);

	return judge;

	
}

 bool CBinaryFile::DeleteRecordById(CString &fileName,int id){
	vector<CString> res=CBinaryFile::ReadAll(fileName);
	vector<CString> splitedString;
	CString split=CString('#');
	int  i = -1;
	int temp;
	do{
		i++;
		splitedString=CUtil::StrSplit(res[i],split);
		temp=CUtil::StringToInteger(splitedString[0]);
	}while(temp!=id);

	for(i=i+1;i<res.size();i++){
		res[i-1]=res[i];
	}
	res.pop_back();
	CFile remove;
	remove.Remove(fileName);
	
	bool judge;
	judge=CBinaryFile::Write(fileName,res);

	return judge;
 }


bool CBinaryFile::SaveCounter(CString &filePath,int counter)
{
	vector<CString> list = CBinaryFile::ReadAll(filePath);
	if (list.empty())
		return false;
	else
	{
		vector<CString> firstRcd = CUtil::StrSplit(list[0],CString("#"));
		firstRcd[0] = CUtil::IntegerToString(counter);
		CString newRcd("");
		for (vector<CString>::iterator ite=firstRcd.begin();ite!=firstRcd.end();++ite)
		{
			newRcd+=*ite+CString("#");
		}
		//删除最后一个#
		newRcd.Delete(newRcd.GetLength()-1,1);
		//把新的第一条记录写入文件
		list[0] = newRcd;

		if(CBinaryFile::Write(filePath,list))
			return true;
		else
			return false;
	}
}