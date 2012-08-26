#include "stdafx.h"
#include "windows.h"
#include "ServerExample.h"
#include "NetworkCoreFactory.h"
#include <iostream>
void TestServer::init()
{
	new NetworkCoreFactory();
	//获得核心网络对象
	m_networkCore = NetworkCoreFactory::getSingleton().createNetworkCore( NetworkCoreFactory::BASERAKNET );
	m_networkCore->addListener( this );
	ServerEnv env;
	env.localIp  = "192.168.1.101";
	env.localPort = 10041;
	env.localPassword = "abc";
	env.localMaxConnectionCount = 10;
	env.localNetworkThreadSleepTime = 1;
	
	m_networkCore->init( &env );
	if( m_networkCore->startService() )
	{
		std::cout<<"start OK"<<std::endl;
	}
	
}

void TestServer::go()
{
	while(onRun())
	{
		m_networkCore->update();
		Sleep(10);
	}
}

bool TestServer::onRun()
{
	
	return true;
}

///表示有一个连接请求被本机接受
void TestServer::onAcceptRemoteConnect( ServerSession * pSession )
{
	std::cout<<"accept OK"<<std::endl;
}

void TestServer::onAccepted( ServerSession * pSession )
{

	std::cout<<"connected OK"<<std::endl;
}

void  TestServer::onConnectFailed( ServerSession * pSession )
{
	std::cout<<"connected failed"<<std::endl;

}

///表示与远端连接非正常断开事件
void  TestServer::onLostConnected( ServerSession * pSession ) 
{
	std::cout<<"connected lost"<<std::endl;
}

void TestServer::onDataRecv( ServerSession * pSession , const MessageData & data )
{

}