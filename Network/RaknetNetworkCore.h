#ifndef _RAKNETNETWORKCORE_HPP_
#define _RAKNETNETWORKCORE_HPP_ 

#pragma once

#include "NetworkCoreInterface.h"
#include "RakNetTypes.h"
#include "BitStream.h"

struct Packet;
class RakPeerInterface;

/** ����Raknet��������Ķ���
@class RaknetNetworkCore

@remarks
	������NetworkCore�������̳С���һ������Raknet��ʵ�ֵ��������Ķ���

@note
	����಻��ֱ�Ӵ�����ֻ��ͨ��NetworkCoreFactory�ഴ����ɾ��

@author ���

@date 2009-09-19

*/

class RaknetNetworkCore : public NetworkCore
{
	friend class NetworkCoreFactory;
	friend class RaknetServerSession;
public:
	RaknetNetworkCore();
	virtual ~RaknetNetworkCore(){};

public:
	///��ʼ��
	virtual bool init( ServerEnv * env ) ;
	
	///��������
	virtual bool startService() ;
	
	///ֹͣ����
	virtual bool stopService() ;
	
	///����
	virtual void update() ;
	
	///����ͨ�Ŷ���
	virtual ServerSession * createServerSession( const std::string & ipAddr , uint16_t port , const std::string & password ) ;
	
	///ɾ��ͨ�Ŷ���
	virtual bool destroyServerSession( ServerSession * pSession );
	
	///���ͨ�Ŷ��������
	virtual SessionManager * getSessionManager( ) ;
	
	///��Ӽ�����
	virtual void addListener( NetWorkCoreListener * pListener );
	
	///ɾ��������
	virtual void removeListener( NetWorkCoreListener * pListener );
private:
	/**��ָ����ַ�������ݵĺ���
	@remarks
		�ú�����Ҫ�����ַ�����ip��ַ���в������ٶȱȽ��������Ե�����һ�����ڶ����Ƶ�ַ�ķ�ʽ���á�

	@return ��ʾ�����Ƿ�ɹ���

	*/
	bool sendData( const std::string & ipAddr , uint16_t port , const MessageData & data );

	//�Զ����Ƶĵ�ַ��ʽ��������
	//bool sendData( long ipAddr , uint16_t port , const MessageData & data );

	///�����û����͵����������
	void processUserPacket( RakNet::Packet * packet );

	///������������͵İ�����
	void processNetworkPacket( RakNet::Packet * packet );

private:
	///��ʾ���������ĵ�����״̬
	enum CORE_STATE {	UNREADY ,		///��ʾδ��ʼ�� 
						READY ,			///��ʾ�Գ�ʼ����δ����
						RUNNING ,		///��ʾ�Գ�ʼ������������
					};
private:
	///���汾��ip
	std::string			m_localIp; 
	
	///���汾�ؼ����˿�
	uint16_t			m_localPort; 
	
	///�����½����
	std::string			m_localPassword;
	
	///���汾�����������
	uint16_t			m_localMaxConnectionCount;
	
	///���汾�����������ѯʱ����
	uint32_t			m_localNetworkThreadSleepTime;
	
	//�����ڲ�����״̬
	CORE_STATE			m_coreState;
	
	///����Raknet�������
	RakNet::RakPeerInterface *	m_localServer;
	
	///�����ַ���������ṩһЩ�������ٶȣ�����ÿ����ջ�Ϸ���
	RakNet::SystemAddress		m_addr;

	///����ͨ�Ŷ��������ָ��
	SessionManager *	m_sessionMgr;
	
	//����Raknet������������Զ�˷�����Ϣ
	RakNet::BitStream	m_bitStream;

	//�������ݶ���,��������ٶȣ�����ÿ����ջ�Ϸ���
	MessageData			m_recvData;

	//���ڱ�����������Զ�˵�session�ļ��ϣ���ʾ��û�������ϵģ������������ת�Ƶ���������
	std::map<unsigned long , ServerSession*>	m_tempSessionMap;
	typedef std::map<unsigned long , ServerSession*> tempSessionMap;
	
	//���ڱ�����Ϊserver��session
	std::map<unsigned long , ServerSession*>	m_serverSessionMap;
	typedef std::map<unsigned long , ServerSession*> serverSessionMap;
	
	//���������ָ��
	std::set<NetWorkCoreListener*>				m_listenerSet;
	typedef std::set<NetWorkCoreListener*>		listenerSet;

};

#endif //_RAKNETNETWORKCORE_HPP_
