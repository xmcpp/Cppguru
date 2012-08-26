#ifndef __ClientExample_H__
#define __ClientExample_H__

#include "ServerApplication.h"
#include "NetworkCoreInterface.h"

class TestClient :public NetWorkCoreListener 
{
public:
	void init();
	void go();
	bool onRun();
public:
	//
	virtual void onAccepted( ServerSession * pSession );

	///表示远端发出的请求被接受事件
	virtual void onConnected( ServerSession * pSession ) {};
	
	virtual void onConnectFailed( ServerSession * pSession );
	///表示与远端连接正常断开连接事件
	virtual void onDisConnected( ServerSession * pSession ) {};

	///表示与远端连接非正常断开事件
	virtual void onLostConnected( ServerSession * pSession ) {};

	///表示有一个连接请求被本机接受
	virtual void onAcceptRemoteConnect( ServerSession * pSession );

	///表示收到远端传送来的数据事件
	virtual void onDataRecv( ServerSession * pSession , const MessageData & data ) {};
private:
	NetworkCore * m_networkCore;
};

#endif //__ClientExample_H__