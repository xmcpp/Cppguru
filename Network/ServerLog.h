#ifndef _SERVERLOG_H_
#define	_SERVERLOG_H_

#pragma  once

enum LOG_TYPE { FILELOG = 0 , DATABASELOG };

/*该枚举用于描述当前日志记录的类型
LOG_INFO				用于记录表示信息的日志
LOG_WARNING				用于记录表示警告的日志
LOG_ERROR				用于记录表示错误的日志
LOG_IMPORTANT			用于记录表示重要的日志<此项是不可屏蔽的，所以用于描述一些不是错误但必须记录的信息>
*/
enum LOG_LEVEL { LOG_INFO = 0 , LOG_WARNING , LOG_ERROR , LOG_IMPORTANT };

class ServerLog
{
public:
	virtual void writeLog( const std::string & str , LOG_LEVEL level = LOG_WARNING ) = 0;
	virtual void setCurrentLogLevel( LOG_LEVEL level ) = 0;
	virtual void setCurrnetOutputLevel( LOG_LEVEL level ) = 0;
	virtual LOG_LEVEL getCurrentLogLevel() = 0;
	virtual LOG_TYPE getLogType() = 0;
};

#endif //_SERVERLOG_H_
