#ifndef _RAKNETSERVERSESSION_H_
#define _RAKNETSERVERSESSION_H_

#pragma once

#include "NetworkCoreInterface.h"

class RakPeerInterface;

/** ����Raknet������ͨ�Ŷ���
@class RaknetServerSession

@remarks
������ServerSession�������̳С���һ������Raknet��ʵ�ֵ�����ͨ�Ŷ���

@note
����಻��ֱ�Ӵ�����ͨ��RaknetNetworkCore�ഴ��

@author ���

@date 2009-09-19

*/

class RaknetServerSession : public ServerSession
{
	friend class RaknetNetworkCore;
private:
	RaknetServerSession( RaknetNetworkCore * pCore );
	virtual ~RaknetServerSession();

public:
	///���ͨ�Ŷ�������
	inline uint16_t getSessionIndex(){ return m_sessionIndex; }
	
	///�Ƿ�����
	inline bool isConnected(){ return m_isConnected; }
	
	///�Ƿ���������
	inline bool isConnector(){ return m_isConnector; }
	
	///ͨ�Ŷ�������
	inline SESSION_TYPE getSessionType(){ return m_type; }
	inline void setSessionType( SESSION_TYPE type ){ m_type = type; }

	///���ip��ַ
	inline const std::string & getRemoteIpAddr(){ return m_ipAddr; }
	inline long getRemoteIpAddrBinary(){ return m_ipAddrBinary; }
	
	///��ö˿ں�
	inline uint16_t getRemotePort(){ return m_port; }
	inline const std::string & getRemotePass(){ return m_pass;}
	///��������
	bool sendData( const MessageData & data );
	
	///����
	void update();
	
	///��Ӽ�����
	void addListener( ServerSessionListener * pListener );
	
	///ɾ��������
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
	
	///ָ��������Ķ����ָ��
	RaknetNetworkCore *	m_core;
	
	///��������߼���
	std::set<ServerSessionListener*>				m_listenerSet;
	typedef std::set<ServerSessionListener*>		listenerSet;
};

#endif //_RAKNETSERVERSESSION_H_
