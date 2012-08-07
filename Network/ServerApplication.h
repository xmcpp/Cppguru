#ifndef _SERVERAPPLICATION_HPP_
#define _SERVERAPPLICATION_HPP_ 

#pragma once


#include "BaseDefine.h"
#include "ServerLogManager.h"
#include "MessageQueneManager.h"

class NetworkCore;

/** 服务器应用程序基础类
	@class ServerApplication

	@remarks
		这个类主要用于定义服务器的基本运行流程，所有服务器应用程序都需要从这个类继承。

	@author 徐淼

	@date 2009-09-15

*/

class ServerApplication
{
public:
	///默认构造函数
	ServerApplication();

	///默认析构函数
	virtual ~ServerApplication();

public:
	/** 服务器启动函数
		@return 返回运行结果

		@remark
			该函数作为整个服务器应用程序的入口函数，将在服务器关闭后返回。
	*/
	bool go();
	

	virtual bool parseConfigFile( const std::string & fileName ) = 0;

	/** 服务器初始化事件函数
	@return 返回运行结果

	@remark
	该函数为纯虚函数，需要子类重载。
	*/
	virtual void onInitialize() {  }

	virtual void onStartUp() {  }

	virtual void onStop() {  }

	virtual void onClearUp() {  }

	virtual bool onRun() { return true; }
	
	/** 服务器处理基本信息的读取
	@param fileName 要解析的配置文件名称
	*/
	void parseBaseConfigFile( const std::string & fileName );

private:
	bool initialize();

	bool startUp();

	bool stop();

	bool clearUp();

	bool run();

protected:
	///服务器基本信息
	std::string			m_localIp; 
	uint16_t			m_localPort; 
	std::string			m_serverPassword;
	uint16_t			m_serverMaxConnectionCount;

	uint32_t			m_mainThreadSleepTime;	///保存当前主线程运行循环中休眠的时间长度，单位毫秒
	uint32_t			m_netWorkThreadSleepTime; //网络收包休眠时间
	
	LOG_LEVEL			m_logLevel;
	LOG_LEVEL			m_outputLogType;
	LOG_TYPE			m_logType;
	
	std::string			m_logFileName;

protected:
	///消息处理队列管理器
	MessageQueneManager	m_queneMgr;

	///网络核心对象
	NetworkCore	*		m_networkCore;
};

#endif //_SERVERAPPLICATION_HPP_ 
