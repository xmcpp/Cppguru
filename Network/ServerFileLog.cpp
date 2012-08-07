#include "stdafx.h"
#include "ServerFileLog.h"
#include <iostream>

ServerFileLog::ServerFileLog( const std::string & filename )
{
	ostream.open( filename.c_str() );
	m_isOpen = ostream.is_open();
}

ServerFileLog::~ServerFileLog()
{
	ostream.close();
}

void ServerFileLog::writeLog( const std::string & str , LOG_LEVEL level ) 
{
	//当前写入级别小于定义的级别时不记录该日志
	if( level >= m_level )
	{
		ostream << str << std::endl;
	}
	
	//当前写入级别小于定义的级别时不输出该日志
	if( level >= m_outputLevel )
	{
		std::cout<< str << std::endl;
	}

	
}