#include "stdafx.h"
#include "ServerLogManager.h"
#include "ServerFileLog.h"

template<> LogManager * Singleton<LogManager>::ms_Singleton	= 0;

LogManager::LogManager()
:m_defaultLog( NULL )
{

}

LogManager::~LogManager()
{
	for( logSet::iterator it = m_logSet.begin() , itend = m_logSet.end() ; it != itend ; it++ )
		if( *it )
			delete *it;

	m_logSet.clear();
}

ServerLog * LogManager::createFileLog( const std::string & fileName )
{
	ServerLog * pLog = new ServerFileLog( fileName );
	if( pLog )
		m_logSet.insert( pLog );

	return pLog;
}

ServerLog * LogManager::createDatabaseLog( )
{
	return NULL;
}

void LogManager::setDefaultLog( ServerLog * pLog )
{
	m_defaultLog = pLog;
}

void LogManager::destroyServerLog( ServerLog * pLog )
{
	m_logSet.erase( pLog );
	if( pLog )
		delete pLog;
}

void LogManager::writeLog( const std::string & str , LOG_LEVEL level )
{
	if( !m_defaultLog ) return;

	m_defaultLog->writeLog( str , level );
}
