#ifndef _SERVERLOGMANAGER_H_
#define	_SERVERLOGMANAGER_H_

#pragma once

#include "ServerLog.h"
#include "Singleton.h"

class ServerLog;

class LogManager : public Singleton<LogManager>
{
public:
	LogManager();
	~LogManager();
public:
	ServerLog * createFileLog( const std::string & fileName );
	ServerLog * createDatabaseLog( );
	void destroyServerLog( ServerLog * pLog );
	
	void setDefaultLog( ServerLog * pLog );
	void writeLog( const std::string & str , LOG_LEVEL level = LOG_WARNING ) ;

private:
	ServerLog * m_defaultLog;
	std::set<ServerLog*> m_logSet;
	typedef std::set<ServerLog*> logSet;

};

#define GLog LogManager::getSingleton()

#endif //_SERVERLOGMANAGER_H_
