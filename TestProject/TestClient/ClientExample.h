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

	///��ʾԶ�˷��������󱻽����¼�
	virtual void onConnected( ServerSession * pSession ) {};
	
	virtual void onConnectFailed( ServerSession * pSession );
	///��ʾ��Զ�����������Ͽ������¼�
	virtual void onDisConnected( ServerSession * pSession ) {};

	///��ʾ��Զ�����ӷ������Ͽ��¼�
	virtual void onLostConnected( ServerSession * pSession ) {};

	///��ʾ��һ���������󱻱�������
	virtual void onAcceptRemoteConnect( ServerSession * pSession );

	///��ʾ�յ�Զ�˴������������¼�
	virtual void onDataRecv( ServerSession * pSession , const MessageData & data ) {};
private:
	NetworkCore * m_networkCore;
};

#endif //__ClientExample_H__