#include "stdafx.h"
#include "windows.h"

#include "ServerApplication.h"
#include "MessageQueneProcessor.h"
#include "NetworkCoreFactory.h"
//#include "utility/IniHelper.h"

#include <sstream>

ServerApplication::ServerApplication()
	:m_mainThreadSleepTime(0) , m_serverMaxConnectionCount( 3000 ) , m_netWorkThreadSleepTime( 30 ) , m_networkCore( NULL )
{
	
}

ServerApplication::~ServerApplication()
{

}

bool ServerApplication::go()
{
	
	if( !initialize() )
		return false;

	//发送初始化事件
	onInitialize();
	
	if( !startUp() )
		return false;

	//发送启动事件
	onStartUp();
	
	//运行循环
	while( onRun() )
	{
		if( !run() )
			return false;
		Sleep( m_mainThreadSleepTime );
	}

	onStop();

	onClearUp();

	return true;
}

bool ServerApplication::initialize()
{
//1.启用日志系统
	new LogManager();
	ServerLog * pLog = NULL;
	
	if( m_logType == FILELOG )
		pLog = LogManager::getSingleton().createFileLog( m_logFileName );
	else
		pLog = LogManager::getSingleton().createDatabaseLog();

	pLog->setCurrentLogLevel( m_logLevel );
	pLog->setCurrnetOutputLevel( m_outputLogType );

	LogManager::getSingleton().setDefaultLog( pLog );
	
	pLog->writeLog( "Log System Start OK!" ,LOG_IMPORTANT );

//2.初始化控制台
	pLog->writeLog( "Initialize Console OK!" ,LOG_IMPORTANT );


//3.初始化服务器核心
	
	pLog->writeLog( "Initialize Server Core ..." ,LOG_INFO );

	//创建网络库核心工厂
	new NetworkCoreFactory();

	//获得核心网络对象
	m_networkCore = NetworkCoreFactory::getSingleton().createNetworkCore( NetworkCoreFactory::BASERAKNET );
	if( !m_networkCore )
	{
		pLog->writeLog( "Create Network Core Failed!" ,LOG_ERROR );
		return false;
	}
	
	pLog->writeLog( "Create Network Core OK!" ,LOG_IMPORTANT );

	ServerEnv env;
	env.localIp = m_localIp;
	env.localPort = m_localPort;
	env.localPassword = m_serverPassword;
	env.localMaxConnectionCount = m_serverMaxConnectionCount;
	env.localNetworkThreadSleepTime = m_netWorkThreadSleepTime;

	if( !m_networkCore->init( &env ) )
	{
		pLog->writeLog( "Initialize Network Core Failed!" ,LOG_ERROR );
		return false;
	}
	pLog->writeLog( "Initialize Network Core OK!" ,LOG_IMPORTANT );

	return true;
}

bool ServerApplication::startUp()
{
	//启动服务器
	if( !m_networkCore->startService() )
	{
		GLog.writeLog( "Start Service Failed!" ,LOG_ERROR );
		return false;
	}
	GLog.writeLog( "Start Service OK!" ,LOG_IMPORTANT );
	
	return true;
}

bool ServerApplication::run()
{
	//网络核心更新，用于处理网络包的收取
	m_networkCore->update();
	return true;
}


bool ServerApplication::stop()
{
	return true;
}

bool ServerApplication::clearUp()
{
	return true;
}

void ServerApplication::parseBaseConfigFile( const std::string & fileName )
{
	/*
	IniHelper ini( fileName );

	//读取基本信息
	ini.getValue( "Local" , "LocalIp" , m_localIp );
	ini.getValue( "Local" , "LocalPort" , m_localPort );
	ini.getValue( "Local" , "LocalPass" , m_serverPassword );
	ini.getValue( "Local" , "LocalMaxConnectionCount" , m_serverMaxConnectionCount );
	ini.getValue( "Local" , "LocalMainThreadSleepTime" , m_mainThreadSleepTime );
	ini.getValue( "Local" , "LocalNetworkThreadSleepTime" , m_netWorkThreadSleepTime );

	//读取日志配置信息
	uint16_t tmp = 0;
	ini.getValue( "Log" , "LogType" , tmp );

	switch ( tmp )
	{
	case 0:
		m_logType = FILELOG;
		break;
	case 1:
		m_logType = DATABASELOG;
		break;
	default:
		m_logType = FILELOG;
	}
	
	//读取日志级别
	tmp = 0;
	ini.getValue( "Log" , "LogLevel" , tmp );

	switch ( tmp )
	{
	case 0:
		m_logLevel = LOG_INFO;
		break;
	case 1:
		m_logLevel = LOG_WARNING;
		break;
	case 2:
		m_logLevel = LOG_ERROR;
		break;
	case 3:
		m_logLevel = LOG_IMPORTANT;
		break;
	default:
		m_logLevel = LOG_INFO;
	}
	
	//读取输出级别
	tmp = 0;
	ini.getValue( "Log" , "OutPutLevel" , tmp );

	switch ( tmp )
	{
	case 0:
		m_outputLogType = LOG_INFO;
		break;
	case 1:
		m_outputLogType = LOG_WARNING;
		break;
	case 2:
		m_outputLogType = LOG_ERROR;
		break;
	case 3:
		m_outputLogType = LOG_IMPORTANT;
		break;
	default:
		m_outputLogType = LOG_INFO;
	}
	
	//读取日志路径
	ini.getValue( "Log" , "LogFilePath" , m_logFileName );*/
}