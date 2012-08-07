#ifndef _RAKNETSESSIONMANAGER_H_
#define _RAKNETSESSIONMANAGER_H_

#include "NetworkCoreInterface.h"

class ServerSession;

/** 基于Raknet的网络通信对象管理器
@class RaknetSessionManager

@remarks
这个类从SessionManager抽象基类继承。是一个基于Raknet库实现的网络通信对象管理器。

@note
这个类不能直接创建，通过RaknetNetworkCore类获得

@author 徐淼

@date 2009-09-19

*/
class RaknetSessionManager : public SessionManager 
{
	friend class RaknetNetworkCore;
private:
	RaknetSessionManager(){};
	virtual ~RaknetSessionManager(){};

public:
	///通信对象注册
	bool registerServerSession( ServerSession * pSession );
	
	///获得通信对象
	ServerSession * getServerSession( uint16_t sessionIndex );
	
	///反注册通信对象
	void unregisterServerSession( uint16_t sessionIndex );
	
	///获得通信对象数目
	uint32_t getServerSessionCount();
	
	///发送数据
	bool sendData( uint16_t sessionIndex , const MessageData & data );
	
	///广播数据
	bool broadSendData( const MessageData & data );
	
	///更新
	void update();

private:

	///保存通信对象
	std::map<uint16_t , ServerSession*> m_sessionMap;
	typedef std::map<uint16_t , ServerSession*> sessionMap;

};

#endif //_RAKNETSESSIONMANAGER_H_
