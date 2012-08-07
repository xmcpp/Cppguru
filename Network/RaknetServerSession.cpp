#include "stdafx.h"
#include "RaknetServerSession.h"
#include "RaknetNetworkCore.h"

RaknetServerSession::RaknetServerSession( RaknetNetworkCore * pCore )
:m_core( pCore )
{

}

RaknetServerSession::~RaknetServerSession()
{

}

void RaknetServerSession::setRemoteIpAddr( const std::string & ipAddr )
{ 
	RakNet::SystemAddress addr;
	addr.SetBinaryAddress( ipAddr.c_str() );
	m_ipAddrBinary = RakNet::SystemAddress::ToInteger(addr);// addr.binaryAddress; 
	m_ipAddr = ipAddr;
}

bool RaknetServerSession::sendData( const MessageData & data )
{
	if( !m_core )
		return false;

	return m_core->sendData( m_ipAddr , m_port , data );
}

void RaknetServerSession::update()
{

}

void RaknetServerSession::addListener( ServerSessionListener * pListener )
{
	if( pListener )
		m_listenerSet.insert( pListener );
}

void RaknetServerSession::removeListener( ServerSessionListener * pListener )
{
	if( pListener )
		m_listenerSet.erase( pListener );
}

void RaknetServerSession::onAccepted( )
{
	std::for_each( m_listenerSet.begin() , m_listenerSet.end() , std::bind2nd( std::mem_fun( &ServerSessionListener::onAccepted ) , this ) );
}

void RaknetServerSession::onConnected( )
{
	std::for_each( m_listenerSet.begin() , m_listenerSet.end() , std::bind2nd( std::mem_fun( &ServerSessionListener::onConnected ) , this ) );
}

void RaknetServerSession::onDisConnected( )
{
	std::for_each( m_listenerSet.begin() , m_listenerSet.end() , std::bind2nd( std::mem_fun( &ServerSessionListener::onDisConnected ) , this ) );
}

void RaknetServerSession::onLostConnected( )
{
	std::for_each( m_listenerSet.begin() , m_listenerSet.end() , std::bind2nd( std::mem_fun( &ServerSessionListener::onLostConnected ) , this ) );
}

void RaknetServerSession::onDataRecv( const MessageData & data )
{
	for( listenerSet::iterator it = m_listenerSet.begin(),itEnd = m_listenerSet.end() ; it != itEnd ; it++ )
	{
		(*it)->onDataRecv( this , data );
	}
}

