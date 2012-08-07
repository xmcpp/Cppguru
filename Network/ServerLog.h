#ifndef _SERVERLOG_H_
#define	_SERVERLOG_H_

#pragma  once

enum LOG_TYPE { FILELOG = 0 , DATABASELOG };

/*��ö������������ǰ��־��¼������
LOG_INFO				���ڼ�¼��ʾ��Ϣ����־
LOG_WARNING				���ڼ�¼��ʾ�������־
LOG_ERROR				���ڼ�¼��ʾ�������־
LOG_IMPORTANT			���ڼ�¼��ʾ��Ҫ����־<�����ǲ������εģ�������������һЩ���Ǵ��󵫱����¼����Ϣ>
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
