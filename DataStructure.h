#pragma  once


typedef int INTEGER;			
typedef bool BOOLE;				
typedef double DOUBLE;			
typedef char VARCHAR[256];		
typedef SYSTEMTIME DATETIME;	



struct DatabaseBlock{
	BOOLE type;			
	VARCHAR name;		
	VARCHAR filepath;	
	DATETIME crtime;	
};