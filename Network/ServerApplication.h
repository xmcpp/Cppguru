#ifndef _SERVERAPPLICATION_HPP_
#define _SERVERAPPLICATION_HPP_ 

#pragma once


#include "BaseDefine.h"
#include "ServerLogManager.h"
#include "MessageQueneManager.h"

class NetworkCore;

/** ������Ӧ�ó��������
	@class ServerApplication

	@remarks
		�������Ҫ���ڶ���������Ļ����������̣����з�����Ӧ�ó�����Ҫ�������̳С�

	@author ���

	@date 2009-09-15

*/

class ServerApplication
{
public:
	///Ĭ�Ϲ��캯��
	ServerApplication();

	///Ĭ����������
	virtual ~ServerApplication();

public:
	/** ��������������
		@return �������н��

		@remark
			�ú�����Ϊ����������Ӧ�ó������ں��������ڷ������رպ󷵻ء�
	*/
	bool go();
	

	virtual bool parseConfigFile( const std::string & fileName ) = 0;

	/** ��������ʼ���¼�����
	@return �������н��

	@remark
	�ú���Ϊ���麯������Ҫ�������ء�
	*/
	virtual void onInitialize() {  }

	virtual void onStartUp() {  }

	virtual void onStop() {  }

	virtual void onClearUp() {  }

	virtual bool onRun() { return true; }
	
	/** ���������������Ϣ�Ķ�ȡ
	@param fileName Ҫ�����������ļ�����
	*/
	void parseBaseConfigFile( const std::string & fileName );

private:
	bool initialize();

	bool startUp();

	bool stop();

	bool clearUp();

	bool run();

protected:
	///������������Ϣ
	std::string			m_localIp; 
	uint16_t			m_localPort; 
	std::string			m_serverPassword;
	uint16_t			m_serverMaxConnectionCount;

	uint32_t			m_mainThreadSleepTime;	///���浱ǰ���߳�����ѭ�������ߵ�ʱ�䳤�ȣ���λ����
	uint32_t			m_netWorkThreadSleepTime; //�����հ�����ʱ��
	
	LOG_LEVEL			m_logLevel;
	LOG_LEVEL			m_outputLogType;
	LOG_TYPE			m_logType;
	
	std::string			m_logFileName;

protected:
	///��Ϣ������й�����
	MessageQueneManager	m_queneMgr;

	///������Ķ���
	NetworkCore	*		m_networkCore;
};

#endif //_SERVERAPPLICATION_HPP_ 
