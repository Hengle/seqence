#ifndef  __logger__  
#define  __logger__  

#include <iostream>  
#include <iomanip>  
#include <fstream>  
#include <string>  
#include <cstdlib>  
#include <stdint.h>  
#include <vector>
#include <cstdlib>  
#include <ctime>  
#include <sstream>
#include "interface.hpp"

namespace Entitas
{
	
	enum LogLevel
	{
		INFO,
		WARN,
		ERR,
		FATAL
	};
	
	
	void InitLogger(const std::string& info_log_filename,
		const std::string& warn_log_filename,
		const std::string& error_log_filename);
	
	
	class Log
	{
		friend void InitLogger(const std::string& info_log_filename,
			const std::string& warn_log_filename,
			const std::string& erro_log_filename);
	
	public:
		Log(LogLevel level) : m_log_level(level) {};
		~Log(void);
	
		template<typename T>
		static std::string tostring(T val)
		{
			std::stringstream ss;
			std::string str;
			ss << val;
			ss >> str;
			return str;
		}
	
		static std::ostream& Start(LogLevel level, std::string text, const std::string &file, const int line, const std::string& function);
		static std::ostream& OStart(const std::string &file, const int line, const std::string& function);
	private:
		static std::ostream& GetStream(LogLevel log_rank);  //���ݵȼ���ȡ��Ӧ����־����� 
		static std::ofstream m_info_log_file;  //��Ϣ���ӵ������  
		static std::ofstream m_warn_log_file;  //������Ϣ�������  
		static std::ofstream m_error_log_file; //������Ϣ�������  
		LogLevel m_log_level;
	};
	
	// ���ݲ�ͬ�ȼ������ò�ͬ����������ж�д  
	#define LOG(text) Log(INFO).Start(INFO, text,__FILE__,__LINE__,__FUNCTION__)  
	
	#define WARN(text) Log(WARN).Start(WARN,text,__FILE__,__LINE__,__FUNCTION__)
	
	#define ERR(text) Log(ERR).Start(ERR,text,__FILE__,__LINE__,__FUNCTION__)
	
	#define PRINT Log(INFO).OStart(__FILE__,__LINE__,__FUNCTION__) 
	
	// �����ռǽ��м��ĸ��ֺ�  
	#define CHECK(a) if(!(a)){ LOG(ERR)<<" CHECK failed "<<endl<<#a<< "= "<< (a)<<endl;abort(); }                                                      
	
	#define CHECK_NOTNULL(a) if( NULL == (a)){ LOG(ERR)<<" CHECK_NOTNULL failed "<< #a << "== NULL "<<endl; abort();}
	
	#define CHECK_NULL(a) if( NULL != (a)){ LOG(ERR)<<" CHECK_NULL failed "<<endl<<#a<< "!= NULL "<<endl; abort();} 
	
	#define CHECK_EQ(a, b) if(!((a) == (b))) { LOG(ERR)<<" CHECK_EQ failed "<< endl<<#a<< "= "<<(a) <<endl<< #b<< "= "<<b<< endl; abort();}  
	
	#define CHECK_NE(a, b) if(!((a) != (b))) { LOG(ERR)<<" CHECK_NE failed "<< endl<< #a<< "= "<<(a)<< endl<<#b<<"= "<<b<< endl; abort();}  
	
	#define CHECK_LT(a, b)if(!((a) < (b))) { LOG(ERR)<<" CHECK_LT failed "<< #a<<"= "<<(a)<< endl<< #b<<"= "<<b<<endl; abort();}  
	
	#define CHECK_GT(a, b) if(!((a) > (b))) { LOG(ERR)<<" CHECK_GT failed "<< endl<< #a<<" = "<<a<< endl<<#b<<"= "<<b<< endl; abort(); } 
	
	#define CHECK_LE(a, b) if(!((a) <= (b))) { LOG(ERR)<<" CHECK_LE failed "<< endl<< #a << "= " <<a<< endl<<#b<<"= "<<b<< endl;abort(); }  
	
	#define CHECK_GE(a, b) if(!((a) >= (b))) { LOG(ERR)<<" CHECK_GE failed "<< endl<<#a<<" = "<<a<< endl<<#b<<"= "<<b<< endl;abort();}  
	
	#define CHECK_DOUBLE_EQ(a, b)do { CHECK_LE((a), (b)+0.000000000000001L); CHECK_GE((a), (b)-0.000000000000001L); }while (0)  
	

}
#endif