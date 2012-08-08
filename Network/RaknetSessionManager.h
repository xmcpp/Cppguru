#ifndef _RAKNETSESSIONMANAGER_H_
#define _RAKNETSESSIONMANAGER_H_

#include "NetworkCoreInterface.h"

class ServerSession;
class RaknetNetworkCore;
/** ����Raknet������ͨ�Ŷ��������
@class RaknetSessionManager

@remarks
������SessionManager�������̳С���һ������Raknet��ʵ�ֵ�����ͨ�Ŷ����������

@note
����಻��ֱ�Ӵ�����ͨ��RaknetNetworkCore����

@author ���

@date 2009-09-19

*/
class RaknetSessionManager : public SessionManager 
{
	friend class RaknetNetworkCore;
private:
	RaknetSessionManager( RaknetNetworkCore * core )
		:m_networkCore(NULL)
	{};
	virtual ~RaknetSessionManager(){};

public:
	bool createSession( bool isServer , const std::string & ipAddr , uint16_t port , const std::string & password );

	///ͨ�Ŷ���ע��
	bool registerServerSession( ServerSession * pSession );
	
	///���ͨ�Ŷ���
	ServerSession * getServerSession( uint16_t sessionIndex );
	
	///��ע��ͨ�Ŷ���
	void unregisterServerSession( uint16_t sessionIndex );
	
	///���ͨ�Ŷ�����Ŀ
	uint32_t getServerSessionCount();
	
	///��������
	bool sendData( uint16_t sessionIndex , const MessageData & data );
	
	///�㲥����
	bool broadSendData( const MessageData & data );
	
	///����
	void update();

private:

	///����ͨ�Ŷ���
	std::map<uint16_t , ServerSession*> m_sessionMap;
	typedef std::map<uint16_t , ServerSession*> sessionMap;
	RaknetNetworkCore * m_networkCore;
};

#endif //_RAKNETSESSIONMANAGER_H_
