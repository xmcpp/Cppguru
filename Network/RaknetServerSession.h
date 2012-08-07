#ifndef _RAKNETSERVERSESSION_H_
#define _RAKNETSERVERSESSION_H_

#pragma once

#include "NetworkCoreInterface.h"

class RakPeerInterface;

/** 基于Raknet的网络通信对象
@class RaknetServerSession

@remarks
这个类从ServerSession抽象基类继承。是一个基于Raknet库实现的网络通信对象。

@note
这个类不能直接创建，通过RaknetNetworkCore类创建

@author 徐淼

@date 2009-09-19

*/

class RaknetServerSession : public ServerSession
{
	friend class RaknetNetworkCore;
private:
	RaknetServerSession( RaknetNetworkCore * pCore );
	virtual ~RaknetServerSession();

public:
	///获得通信对象索引
	inline uint16_t getSessionIndex(){ return m_sessionIndex; }
	
	///是否连接
	inline bool isConnected(){ return m_isConnected; }
	
	///是否是连接者
	inline bool isConnector(){ return m_isConnector; }
	
	///通信对象类型
	inline SESSION_TYPE getSessionType(){ return m_type; }
	inline void setSessionType( SESSION_TYPE type ){ m_type = type; }

	///获得ip地址
	inline const std::string & getRemoteIpAddr(){ return m_ipAddr; }
	inline long getRemoteIpAddrBinary(){ return m_ipAddrBinary; }
	
	///获得端口号
	inline uint16_t getRemotePort(){ return m_port; }
	inline const std::string & getRemotePass(){ return m_pass;}
	///发送数据
	bool sendData( const MessageData & data );
	
	///更新
	void update();
	
	///添加监听者
	void addListener( ServerSessionListener * pListener );
	
	///删除监听者
	void removeListener( ServerSessionListener * pListener );
private:
	void onAccepted( );
	void onConnected( ) ;
	void onDisConnected( ) ;
	void onLostConnected( ) ;
	void onDataRecv( const MessageData & data );

	inline void setSessionIndex( uint16_t index ){ m_sessionIndex = index; }
	inline void setConnected( bool bVal ){ m_isConnected = bVal; }
	inline void setConnector( bool bVal ){ m_isConnector = bVal; }
	inline void setRemotePort( uint16_t port ){ m_port = port; }
	void setRemoteIpAddr( const std::string & ipAddr );
	void setRemotePass( const std::string & pass ){ m_pass = pass; }

private:
	uint16_t			m_sessionIndex;
	bool				m_isConnected;
	bool				m_isConnector;
	SESSION_TYPE		m_type;
	std::string			m_ipAddr;
	long				m_ipAddrBinary;
	uint16_t			m_port;
	std::string			m_pass;
	
	///指向网络核心对象的指针
	RaknetNetworkCore *	m_core;
	
	///保存监听者集合
	std::set<ServerSessionListener*>				m_listenerSet;
	typedef std::set<ServerSessionListener*>		listenerSet;
};

#endif //_RAKNETSERVERSESSION_H_
