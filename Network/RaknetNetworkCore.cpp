#include "stdafx.h"

#include "RaknetNetworkCore.h"
#include "RaknetServerSession.h"
#include "RaknetSessionManager.h"

//#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"

RaknetNetworkCore::RaknetNetworkCore()
:m_localServer( 0 ) , m_coreState( UNREADY ) , m_localPort( 0 ) , m_localMaxConnectionCount( 0 ) , m_localNetworkThreadSleepTime( 0 )
,m_sessionMgr( 0 )
{
	memset( &m_recvData , 0 , sizeof( m_recvData ) );
}

bool RaknetNetworkCore::init( ServerEnv * env )
{
	if( !env ) 
		return false;
	
	//获取需要的服务器配置信息
	m_localIp = env->localIp;
	m_localPort = env->localPort;
	m_localPassword = env->localPassword;
	m_localMaxConnectionCount = env->localMaxConnectionCount;
	m_localNetworkThreadSleepTime = env->localNetworkThreadSleepTime;

	//初始化session管理器对象
	if( !m_sessionMgr )
	{
		m_sessionMgr = new RaknetSessionManager();
	}
	
	//设置服务器状态
	m_coreState = READY;

	return true;
}

bool RaknetNetworkCore::startService()
{
	if( m_coreState == UNREADY || m_coreState == RUNNING )
		return false;

	//创建Raknet处理线程
	if( m_localServer )
	{
		RakNet::RakPeerInterface::DestroyInstance( m_localServer );
		m_localServer = NULL;
	}

	m_localServer = RakNet::RakPeerInterface::GetInstance();
	if( !m_localServer )
		return false;


	//启动Raknet线程监听
	RakNet::SocketDescriptor Des( m_localPort , m_localIp.c_str() );
	m_localServer->SetIncomingPassword( m_localPassword.c_str() , ( uint32_t )m_localPassword.length() );
	if( !m_localServer->Startup( m_localMaxConnectionCount , &Des , 1 ) )
		return false;

	m_localServer->SetMaximumIncomingConnections( m_localMaxConnectionCount );
	
	
	m_coreState = RUNNING;

	return true;
}

bool RaknetNetworkCore::stopService()
{
	if( m_coreState != RUNNING )
		return false;
	
	m_coreState = READY;

	return true;
}

void RaknetNetworkCore::update()
{
	if( m_coreState != RUNNING )
		return ;

	RakNet::Packet * packet = NULL;
	for ( packet = m_localServer->Receive(); packet ; packet = m_localServer->Receive() )
	{
		switch ( packet->data[0] )
		{
		case ID_USER_PACKET_ENUM :  
			processUserPacket( packet ); //处理用户自定义事件
			break;
		default:
			processNetworkPacket( packet ); //处理网络层事件
			break;
		}

		//析构packet，防止内存泄露
		m_localServer->DeallocatePacket( packet );
		packet = NULL;
	}
}

SessionManager * RaknetNetworkCore::getSessionManager()
{
	if( m_coreState == UNREADY )
		return false;

	return m_sessionMgr;
}

ServerSession * RaknetNetworkCore::createServerSession( const std::string & ipAddr , uint16_t port , const std::string & password ) 
{
	if( m_coreState != RUNNING )
		return NULL;
	
	//发送与远端连接的请求
	if( !m_localServer->Connect( ipAddr.c_str() , port , password.c_str() , (uint32_t)password.length() ) )
	{
		//连接请求失败，返回空
		return NULL;
	}

	//创建Session对象
	RaknetServerSession * pSession = new RaknetServerSession( this );

	//设置连接成功为false
	pSession->setConnected( false );

	//由于自身连接远端服务器，即为connector,故设置为true
	pSession->setConnector( true );

	//设置远端ip地址和端口
	pSession->setRemoteIpAddr( ipAddr );
	pSession->setRemotePort( (unsigned short)port );
	pSession->setRemotePass( password );

	//设置本Session的类型为INVALID，因为还未连接成功，故属于无效session
	pSession->setSessionType( INVALID );
		
	//将session保存等待回应
	m_addr.SetBinaryAddress( ipAddr.c_str());

	m_addr.SetPort( port );
	m_tempSessionMap.insert( std::make_pair( m_addr , pSession ) );

	return pSession ;
}

bool RaknetNetworkCore::destroyServerSession( ServerSession * pSession )
{
	if( !pSession )
		return false;
	
	if( pSession->getSessionType() == INVALID )
	{
		//表示当前Session还没有成功连接，在本地temp中直接寻找并删除
		m_addr.SetBinaryAddress( pSession->getRemoteIpAddr().c_str() );
		m_addr.SetPort( pSession->getRemotePort() );
		
		tempSessionMap::iterator it = m_tempSessionMap.find( m_addr );
		if( it != m_tempSessionMap.end() )
			m_tempSessionMap.erase( it );
		else
		{
			//没有找到该对象，事实应该不会发生这种事情
		}
	}
	else
		m_sessionMgr->unregisterServerSession( pSession->getSessionIndex() );
	
	//删除session对象
	delete pSession;

	return true;
}

void RaknetNetworkCore::addListener( NetWorkCoreListener * pListener )
{
	if( pListener )
		m_listenerSet.insert( pListener );
}

void RaknetNetworkCore::removeListener( NetWorkCoreListener * pListener )
{
	if( pListener )
		m_listenerSet.erase( pListener );
}

bool RaknetNetworkCore::sendData( const std::string & ipAddr , uint16_t port , const MessageData & data )
{
	if( m_coreState != RUNNING )
		return false;
	
	//设置发送地址
	m_addr.SetBinaryAddress( ipAddr.c_str() );
	m_addr.SetPort( port );
	
	//构造发送数据
	m_bitStream.Reset();
	m_bitStream.Write( ( uint8_t )ID_USER_PACKET_ENUM );
	m_bitStream.Write( ( uint8_t )data.messageType );
	m_bitStream.Write( data.messageID );
	m_bitStream.WriteBits( ( uint8_t * )data.data , data.size * 8 );
	
	//发送
	return ( m_localServer->Send( &m_bitStream , HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_addr , false ) );
}

/*
bool RaknetNetworkCore::sendData( long ipAddr , uint16_t port , const MessageData & data )
{
	if( m_coreState != RUNNING )
		return false;
	
	//设置发送地址
	
	m_addr.binaryAddress = ipAddr;
	m_addr.SetPort( port );

	//构造发送数据
	m_bitStream.Reset();
	m_bitStream.Write( ( uint8_t )ID_USER_PACKET_ENUM );
	m_bitStream.Write( ( uint8_t )data.messageType );
	m_bitStream.Write( data.messageID );
	m_bitStream.WriteBits( ( uint8_t * )data.data , data.size * 8 );

	//发送
	return ( m_localServer->Send( &m_bitStream , HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_addr , false ) );

}*/

void RaknetNetworkCore::processUserPacket( RakNet::Packet * packet )
{
	if( !packet )
		return;

	RaknetServerSession * pSession = dynamic_cast<RaknetServerSession*>( m_sessionMgr->getServerSession( packet->guid.systemIndex ) );
	if( !pSession )
		return;
	
	/*这里为了保证操作效率对传入的数据采取特殊处理。一般的处理是构造bitstream对象
	  ，但是构造对象开销很大，所以这里直接对data进行访问。data的布局如下：
	  datatype    标示数据包网络类型， 8位 1字节
	  messagetype 标示数据包应用层类型 8位 1字节
	  messageid   标示应用层消息的id   16位 2字节
	  data        标示数据内容，       长度 = packet长度 - ( 8 + 8 + 16 ) = packet长度 - 4字节

	  根据上述描述形成如下代码。另外由于onDataRecv是同步事件，所以可以将packet的data
	  直接传进去供应用层使用。在应用层如果需要保存则需要根据size的长度对data进行深拷贝
	*/

	//读取消息类型
	m_recvData.messageType = *( packet->data + 1 );

	//读取消息ID
	m_recvData.messageID = *( uint16_t* )( packet->data + 2 );
	
	//记录发送者的session id
	m_recvData.senderIndex = pSession->getSessionIndex();

	//读取数据
	m_recvData.size = packet->length - 4;
	m_recvData.data = packet->data + 4;

	//发送接收到数据事件
	pSession->onDataRecv( m_recvData );
}

void RaknetNetworkCore::processNetworkPacket( RakNet::Packet * packet )
{
	switch ( packet->data[0] )
	{
	case ID_CONNECTION_REQUEST_ACCEPTED : //表示连接远端服务器成功
		{
			//查询临时Session对象
			tempSessionMap::iterator it = m_tempSessionMap.find( packet->systemAddress );
			if( it == m_tempSessionMap.end() )
			{
				//表示当前的session未找到，出现未请求的session的回应，出现的可能是用户创建session后未等待回应直接调用destroy方法删除。
				return ;
			}
			RaknetServerSession * pSession = dynamic_cast<RaknetServerSession *>( it->second );

			if( !pSession )
				return;
			
			//从tempSessionMap中删除该Session
			m_tempSessionMap.erase( it );

			//设置连接成功
			pSession->setConnected( true );
			
			//设置本Session的类型为UNKNOWN，因为目前只是获得了连接成功的消息，无法判定类型。如果
			//要确定类型必须通过后续的应用层通信才能确定
			pSession->setSessionType( UNKNOWN );

			//设置Session的索引号
			pSession->setSessionIndex( packet->guid.systemIndex );
			
			//将该session注册到SessionManager中
			m_sessionMgr->registerServerSession( pSession );

			//发送连接成功的事件
			pSession->onAccepted();
		}
		break;
	case ID_CONNECTION_ATTEMPT_FAILED : //表示连接服务器失败

		break;
	case ID_DISCONNECTION_NOTIFICATION: //表示连接正常关闭
		{
			RaknetServerSession * pSession = dynamic_cast<RaknetServerSession *>( m_sessionMgr->getServerSession( packet->guid.systemIndex ) );
			if( pSession )
			{
				pSession->setConnected( false );

				//反注册该连接对象
				m_sessionMgr->unregisterServerSession( packet->guid.systemIndex );

				//发送断开连接事件
				pSession->onDisConnected();

				//删除该连接对象
				delete pSession;
			}
		}
		break;
	case ID_CONNECTION_LOST: 			//表示连接非正常关闭（掉线)
		{
			RaknetServerSession * pSession = dynamic_cast<RaknetServerSession *>( m_sessionMgr->getServerSession( packet->guid.systemIndex ) );
			if( pSession )
			{
				pSession->setConnected( false );

				//反注册该连接对象
				m_sessionMgr->unregisterServerSession( packet->guid.systemIndex );

				//发送丢失连接事件
				pSession->onLostConnected();

				//删除该连接对象
				delete pSession;
			}
		}
		break;
	case ID_NEW_INCOMING_CONNECTION:	//表示接受远端的一个连接
		{
			//创建Session对象
			RaknetServerSession * pSession = new RaknetServerSession( this );

			//设置连接成功
			pSession->setConnected( true );

			//由于该事件表示接受远端服务器的连接，所以自身为不是连接者，故设置为false
			pSession->setConnector( false );

			//设置远端ip地址和端口
			pSession->setRemoteIpAddr( packet->systemAddress.ToString( false ) );
			pSession->setRemotePort( packet->systemAddress.GetPort() );

			//设置本Session的类型为UNKNOWN，因为目前只是获得了连接成功的消息，无法判定类型。如果
			//要确定类型必须通过后续的应用层通信才能确定
			pSession->setSessionType( UNKNOWN );
			pSession->setSessionIndex( packet->guid.systemIndex );

			//设置Session的索引号
			m_sessionMgr->registerServerSession( pSession );

			//发送接受远端连接的事件
			std::for_each( m_listenerSet.begin() , m_listenerSet.end() , std::bind2nd( std::mem_fun( &NetWorkCoreListener::onAcceptRemoteConnect ) , pSession ) );
		}
		break;
	default:
		//有未处理的事件
		break;
	}
}