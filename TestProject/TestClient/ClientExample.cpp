#include "stdafx.h"
#include "windows.h"
#include "ClientExample.h"
#include "NetworkCoreFactory.h"
#include <iostream>
void TestClient::init()
{
	new NetworkCoreFactory();
	//获得核心网络对象
	m_networkCore = NetworkCoreFactory::getSingleton().createNetworkCore( NetworkCoreFactory::BASERAKNET );
	m_networkCore->addListener( this );
	ServerEnv env;
	//env.localIp  = "192.168.1.102";
	env.localPort = 10044;
	env.localPassword = "abc";
	env.localMaxConnectionCount = 10;
	env.localNetworkThreadSleepTime = 1;
	
	m_networkCore->init( &env );
	m_networkCore->startService();
	
	ServerSession * session = m_networkCore->createServerSession( "192.168.1.101",10041,"abc");
	if ( session )
	{
		std::cout<<"ok"<<std::endl;
	}

}

void TestClient::go()
{
	while(onRun())
	{
		m_networkCore->update();
		Sleep(10);
	}
}

bool TestClient::onRun()
{
	
	return true;
}

///表示有一个连接请求被本机接受
void TestClient::onAcceptRemoteConnect( ServerSession * pSession )
{
	std::cout<<"accept OK"<<std::endl;
}

void TestClient::onAccepted( ServerSession * pSession )
{

	std::cout<<"connected OK"<<std::endl;
}

void  TestClient::onConnectFailed( ServerSession * pSession )
{
	std::cout<<"connected failed"<<std::endl;

}