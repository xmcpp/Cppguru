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
	
	//��ȡ��Ҫ�ķ�����������Ϣ
	m_localIp = env->localIp;
	m_localPort = env->localPort;
	m_localPassword = env->localPassword;
	m_localMaxConnectionCount = env->localMaxConnectionCount;
	m_localNetworkThreadSleepTime = env->localNetworkThreadSleepTime;

	//��ʼ��session����������
	if( !m_sessionMgr )
	{
		m_sessionMgr = new RaknetSessionManager();
	}
	
	//���÷�����״̬
	m_coreState = READY;

	return true;
}

bool RaknetNetworkCore::startService()
{
	if( m_coreState == UNREADY || m_coreState == RUNNING )
		return false;

	//����Raknet�����߳�
	if( m_localServer )
	{
		RakNet::RakPeerInterface::DestroyInstance( m_localServer );
		m_localServer = NULL;
	}

	m_localServer = RakNet::RakPeerInterface::GetInstance();
	if( !m_localServer )
		return false;


	//����Raknet�̼߳���
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
			processUserPacket( packet ); //�����û��Զ����¼�
			break;
		default:
			processNetworkPacket( packet ); //����������¼�
			break;
		}

		//����packet����ֹ�ڴ�й¶
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
	
	//������Զ�����ӵ�����
	if( !m_localServer->Connect( ipAddr.c_str() , port , password.c_str() , (uint32_t)password.length() ) )
	{
		//��������ʧ�ܣ����ؿ�
		return NULL;
	}

	//����Session����
	RaknetServerSession * pSession = new RaknetServerSession( this );

	//�������ӳɹ�Ϊfalse
	pSession->setConnected( false );

	//������������Զ�˷���������Ϊconnector,������Ϊtrue
	pSession->setConnector( true );

	//����Զ��ip��ַ�Ͷ˿�
	pSession->setRemoteIpAddr( ipAddr );
	pSession->setRemotePort( (unsigned short)port );
	pSession->setRemotePass( password );

	//���ñ�Session������ΪINVALID����Ϊ��δ���ӳɹ�����������Чsession
	pSession->setSessionType( INVALID );
		
	//��session����ȴ���Ӧ
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
		//��ʾ��ǰSession��û�гɹ����ӣ��ڱ���temp��ֱ��Ѱ�Ҳ�ɾ��
		m_addr.SetBinaryAddress( pSession->getRemoteIpAddr().c_str() );
		m_addr.SetPort( pSession->getRemotePort() );
		
		tempSessionMap::iterator it = m_tempSessionMap.find( m_addr );
		if( it != m_tempSessionMap.end() )
			m_tempSessionMap.erase( it );
		else
		{
			//û���ҵ��ö�����ʵӦ�ò��ᷢ����������
		}
	}
	else
		m_sessionMgr->unregisterServerSession( pSession->getSessionIndex() );
	
	//ɾ��session����
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
	
	//���÷��͵�ַ
	m_addr.SetBinaryAddress( ipAddr.c_str() );
	m_addr.SetPort( port );
	
	//���췢������
	m_bitStream.Reset();
	m_bitStream.Write( ( uint8_t )ID_USER_PACKET_ENUM );
	m_bitStream.Write( ( uint8_t )data.messageType );
	m_bitStream.Write( data.messageID );
	m_bitStream.WriteBits( ( uint8_t * )data.data , data.size * 8 );
	
	//����
	return ( m_localServer->Send( &m_bitStream , HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_addr , false ) );
}

/*
bool RaknetNetworkCore::sendData( long ipAddr , uint16_t port , const MessageData & data )
{
	if( m_coreState != RUNNING )
		return false;
	
	//���÷��͵�ַ
	
	m_addr.binaryAddress = ipAddr;
	m_addr.SetPort( port );

	//���췢������
	m_bitStream.Reset();
	m_bitStream.Write( ( uint8_t )ID_USER_PACKET_ENUM );
	m_bitStream.Write( ( uint8_t )data.messageType );
	m_bitStream.Write( data.messageID );
	m_bitStream.WriteBits( ( uint8_t * )data.data , data.size * 8 );

	//����
	return ( m_localServer->Send( &m_bitStream , HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_addr , false ) );

}*/

void RaknetNetworkCore::processUserPacket( RakNet::Packet * packet )
{
	if( !packet )
		return;

	RaknetServerSession * pSession = dynamic_cast<RaknetServerSession*>( m_sessionMgr->getServerSession( packet->guid.systemIndex ) );
	if( !pSession )
		return;
	
	/*����Ϊ�˱�֤����Ч�ʶԴ�������ݲ�ȡ���⴦��һ��Ĵ����ǹ���bitstream����
	  �����ǹ���������ܴ���������ֱ�Ӷ�data���з��ʡ�data�Ĳ������£�
	  datatype    ��ʾ���ݰ��������ͣ� 8λ 1�ֽ�
	  messagetype ��ʾ���ݰ�Ӧ�ò����� 8λ 1�ֽ�
	  messageid   ��ʾӦ�ò���Ϣ��id   16λ 2�ֽ�
	  data        ��ʾ�������ݣ�       ���� = packet���� - ( 8 + 8 + 16 ) = packet���� - 4�ֽ�

	  �������������γ����´��롣��������onDataRecv��ͬ���¼������Կ��Խ�packet��data
	  ֱ�Ӵ���ȥ��Ӧ�ò�ʹ�á���Ӧ�ò������Ҫ��������Ҫ����size�ĳ��ȶ�data�������
	*/

	//��ȡ��Ϣ����
	m_recvData.messageType = *( packet->data + 1 );

	//��ȡ��ϢID
	m_recvData.messageID = *( uint16_t* )( packet->data + 2 );
	
	//��¼�����ߵ�session id
	m_recvData.senderIndex = pSession->getSessionIndex();

	//��ȡ����
	m_recvData.size = packet->length - 4;
	m_recvData.data = packet->data + 4;

	//���ͽ��յ������¼�
	pSession->onDataRecv( m_recvData );
}

void RaknetNetworkCore::processNetworkPacket( RakNet::Packet * packet )
{
	switch ( packet->data[0] )
	{
	case ID_CONNECTION_REQUEST_ACCEPTED : //��ʾ����Զ�˷������ɹ�
		{
			//��ѯ��ʱSession����
			tempSessionMap::iterator it = m_tempSessionMap.find( packet->systemAddress );
			if( it == m_tempSessionMap.end() )
			{
				//��ʾ��ǰ��sessionδ�ҵ�������δ�����session�Ļ�Ӧ�����ֵĿ������û�����session��δ�ȴ���Ӧֱ�ӵ���destroy����ɾ����
				return ;
			}
			RaknetServerSession * pSession = dynamic_cast<RaknetServerSession *>( it->second );

			if( !pSession )
				return;
			
			//��tempSessionMap��ɾ����Session
			m_tempSessionMap.erase( it );

			//�������ӳɹ�
			pSession->setConnected( true );
			
			//���ñ�Session������ΪUNKNOWN����ΪĿǰֻ�ǻ�������ӳɹ�����Ϣ���޷��ж����͡����
			//Ҫȷ�����ͱ���ͨ��������Ӧ�ò�ͨ�Ų���ȷ��
			pSession->setSessionType( UNKNOWN );

			//����Session��������
			pSession->setSessionIndex( packet->guid.systemIndex );
			
			//����sessionע�ᵽSessionManager��
			m_sessionMgr->registerServerSession( pSession );

			//�������ӳɹ����¼�
			pSession->onAccepted();
		}
		break;
	case ID_CONNECTION_ATTEMPT_FAILED : //��ʾ���ӷ�����ʧ��

		break;
	case ID_DISCONNECTION_NOTIFICATION: //��ʾ���������ر�
		{
			RaknetServerSession * pSession = dynamic_cast<RaknetServerSession *>( m_sessionMgr->getServerSession( packet->guid.systemIndex ) );
			if( pSession )
			{
				pSession->setConnected( false );

				//��ע������Ӷ���
				m_sessionMgr->unregisterServerSession( packet->guid.systemIndex );

				//���ͶϿ������¼�
				pSession->onDisConnected();

				//ɾ�������Ӷ���
				delete pSession;
			}
		}
		break;
	case ID_CONNECTION_LOST: 			//��ʾ���ӷ������رգ�����)
		{
			RaknetServerSession * pSession = dynamic_cast<RaknetServerSession *>( m_sessionMgr->getServerSession( packet->guid.systemIndex ) );
			if( pSession )
			{
				pSession->setConnected( false );

				//��ע������Ӷ���
				m_sessionMgr->unregisterServerSession( packet->guid.systemIndex );

				//���Ͷ�ʧ�����¼�
				pSession->onLostConnected();

				//ɾ�������Ӷ���
				delete pSession;
			}
		}
		break;
	case ID_NEW_INCOMING_CONNECTION:	//��ʾ����Զ�˵�һ������
		{
			//����Session����
			RaknetServerSession * pSession = new RaknetServerSession( this );

			//�������ӳɹ�
			pSession->setConnected( true );

			//���ڸ��¼���ʾ����Զ�˷����������ӣ���������Ϊ���������ߣ�������Ϊfalse
			pSession->setConnector( false );

			//����Զ��ip��ַ�Ͷ˿�
			pSession->setRemoteIpAddr( packet->systemAddress.ToString( false ) );
			pSession->setRemotePort( packet->systemAddress.GetPort() );

			//���ñ�Session������ΪUNKNOWN����ΪĿǰֻ�ǻ�������ӳɹ�����Ϣ���޷��ж����͡����
			//Ҫȷ�����ͱ���ͨ��������Ӧ�ò�ͨ�Ų���ȷ��
			pSession->setSessionType( UNKNOWN );
			pSession->setSessionIndex( packet->guid.systemIndex );

			//����Session��������
			m_sessionMgr->registerServerSession( pSession );

			//���ͽ���Զ�����ӵ��¼�
			std::for_each( m_listenerSet.begin() , m_listenerSet.end() , std::bind2nd( std::mem_fun( &NetWorkCoreListener::onAcceptRemoteConnect ) , pSession ) );
		}
		break;
	default:
		//��δ������¼�
		break;
	}
}