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
	//��ǰд�뼶��С�ڶ���ļ���ʱ����¼����־
	if( level >= m_level )
	{
		ostream << str << std::endl;
	}
	
	//��ǰд�뼶��С�ڶ���ļ���ʱ���������־
	if( level >= m_outputLevel )
	{
		std::cout<< str << std::endl;
	}

	
}