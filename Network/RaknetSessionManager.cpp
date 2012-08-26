#include "stdafx.h"
#include "RaknetSessionManager.h"
#include "RaknetNetworkCore.h"

bool RaknetSessionManager::createSession( bool isServer , const std::string & ipAddr , uint16_t port , const std::string & password )
{
	return true;

		
}

bool RaknetSessionManager::registerServerSession( ServerSession * pSession )
{
	if( !pSession ) return false;

	uint16_t sessionIndex = pSession->getSessionIndex();

	//检查该Session是否存在，如果存在则返回false
	sessionMap::iterator it =  m_sessionMap.find( sessionIndex );
	if( it != m_sessionMap.end() )
		return false;

	//将该Session插入到集合中
	m_sessionMap.insert( std::make_pair( sessionIndex , pSession ) );
	return true;
}

ServerSession * RaknetSessionManager::getServerSession( uint16_t sessionIndex )
{
	ServerSession * pSession = NULL;

	sessionMap::iterator it =  m_sessionMap.find( sessionIndex );

	if( it != m_sessionMap.end() )
		pSession = it->second;		

	return pSession;
}

void RaknetSessionManager::unregisterServerSession( uint16_t sessionIndex )
{
	//只负责反注册，不负责删除
	sessionMap::iterator it =  m_sessionMap.find( sessionIndex );

	if( it != m_sessionMap.end() )
	{
		m_sessionMap.erase( it );
	}
}

uint32_t RaknetSessionManager::getServerSessionCount()
{
	return (uint32_t)m_sessionMap.size();
}

bool RaknetSessionManager::sendData( uint16_t sessionIndex , const MessageData & data )
{
	ServerSession * pSession = getServerSession( sessionIndex );
	if( !pSession )
		return false;

	return pSession->sendData( data );
}

bool RaknetSessionManager::broadSendData( const MessageData & data )
{
	for( sessionMap::iterator it = m_sessionMap.begin() , itend = m_sessionMap.end() ; it != itend ; it++ )
	{
		if( it->second )
			it->second->sendData( data );
	}

	return true;
}

void RaknetSessionManager::update()
{
	for( sessionMap::iterator it = m_sessionMap.begin() , itend = m_sessionMap.end() ; it != itend ; it++ )
	{
		if( it->second )
			it->second->update();
	}
}