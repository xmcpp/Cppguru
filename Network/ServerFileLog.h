#ifndef _SERVERFILELOG_H_
#define	_SERVERFILELOG_H_

#pragma  once

#include "ServerLog.h"
#include <fstream>

class ServerFileLog : public ServerLog
{
	friend class LogManager;
private:
	ServerFileLog( const std::string & filename );
	~ServerFileLog();
public:
	void writeLog( const std::string & str , LOG_LEVEL level = LOG_WARNING ) ;
	
	virtual void setCurrnetOutputLevel( LOG_LEVEL level ) { m_outputLevel = level; }
	inline void setCurrentLogLevel( LOG_LEVEL level ) { m_level = level; }
	inline LOG_LEVEL getCurrentLogLevel() { return m_level; }
	inline LOG_TYPE getLogType() { return FILELOG; }

private:
	LOG_LEVEL m_level;
	LOG_LEVEL m_outputLevel;
	bool m_isOpen;

	std::ofstream ostream;
};

#endif //_SERVERFILELOG_H_
