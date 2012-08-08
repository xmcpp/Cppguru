#ifndef _NETWORKCOREINTERFACE_HPP_
#define _NETWORKCOREINTERFACE_HPP_ 

#pragma once

/** ���ļ�����������ĵ����г������

@remarks
	�����Ŀ������ϣ���ܹ����û���Ӧ������������ʵ�ָ��뿪�������ڶ�������ʵ�ֽ����޸�
	ʱ����Ӱ���ϲ��߼���Ŀǰ�ṩ��һ��ʵ���ǻ���Raknet��ġ���ô���������ĳ���Ҳ����ʵ��һ
	��IOCP�ĵײ㣬����������ʵ�ֱ�����ϲ�Ӧ����˵��ȫ͸����

@note

@author ���

@date 2009-09-19

*/


#include "BaseDefine.h"


class ServerSession;
class SessionManager;


enum SESSION_TYPE{	INVALID = 0,		///��ʾ��Ч���ӣ���ʱ��û����ͨ
					UNKNOWN	 ,			///��ʾ��Ч���ӣ���ʱ����֪�����
					LOGINSERVER  ,		///��ʾ��Ч���ӣ��Է���Login������
					PROXYSERVER   ,		///��ʾ��Ч���ӣ��Է��Ǵ��������
					MAPSERVER  ,		///��ʾ��Ч���ӣ��Է��ǵ�ͼ������
					MANAGESERVER  ,		///��ʾ��Ч���ӣ��Է��ǹ��������
					DBSERVER  ,			///��ʾ��Ч���ӣ��Է������ݿ������
					LOCAL  ,			///
					CLIENT  ,			///��ʾ��Ч���ӣ��Է��ǿͻ���
					USERDEFINE = 100	///�����Ժ���չ
};


/** ��������¼�����
@class NetWorkCoreListener

@remarks
	�����������������������п��Լ������¼���

@note

@author ���

@date 2009-09-19

*/
/*
class NetWorkCoreListener
{
public:
	//��ʾ��һ���������󱻱�������
	virtual void onAcceptRemoteConnect( ServerSession * pSession ) = 0;
};*/


/** ����ͨ�Ŷ������
@class ServerSessionListener

@remarks
	���������������ͨ�Ŷ����п��Լ������¼���

@note

@author ���

@date 2009-09-19

*/
class NetWorkCoreListener
{
public:
	///��ʾ�������������󱻽����¼�
	virtual void onAccepted( ServerSession * pSession ) {};
	
	///��ʾԶ�˷��������󱻽����¼�
	virtual void onConnected( ServerSession * pSession ) {};
	
	///��ʾ��Զ�����������Ͽ������¼�
	virtual void onDisConnected( ServerSession * pSession ) {};
	
	///��ʾ��Զ�����ӷ������Ͽ��¼�
	virtual void onLostConnected( ServerSession * pSession ) {};
	
	///��ʾ��һ���������󱻱�������
	virtual void onAcceptRemoteConnect( ServerSession * pSession ){};

	///��ʾ�յ�Զ�˴������������¼�
	virtual void onDataRecv( ServerSession * pSession , const MessageData & data ) {};
};


/** ������Ĺ��ܳ������
@class NetworkCore

@remarks
	�����������������Ļ������ܳ�����һ��������ࡣ

@note

@author ���

@date 2009-09-19

*/

class NetworkCore
{
public:
	/**��������ʼ������
	@remarks
		�ú�����������Ϊ���������������ʼ����������ʼ��������ServerEnv���塣��ʵ�ֹ����п��԰�����Ҫ
		ѡȡ�ýṹ���еĲ�����

	@param env �������еķ���������ʱ�������ɷ���������ʱ��ȡ����ʼ����

	@return ��ʾ��ʼ���Ƿ�ɹ���

	*/
	virtual bool init( ServerEnv * env ) = 0;

	/**���������������
	@remarks
		�ú����������ǻ��ڳ�ʼ�����������е�һ����������Ҫ������ڳ�ʼ���������������������Ĺ��ܡ�
	
	@return ��ʾ�����Ƿ�ɹ���

	*/
	virtual bool startService() = 0;

	/**�������ֹͣ����
	@remarks
		�ú����������Ǹ���ֹͣ��������������Ĺ��ܡ�

	@return ��ʾֹͣ�Ƿ�ɹ���

	*/
	virtual bool stopService() = 0;

	/**���������º���
	@remarks
		�ú�����������Ϊ�������������ṩһ���ƶ�����ڣ��ڸú����п��Դ����������ȡ�ȹ��ܡ�

	*/
	virtual void update() = 0;

	/**��������ͨ��Session
	@remarks
		�ú����������ǻ��ڵ�ǰ��������Ĵ���һ��ͨ��Session����
	
	@return ���سɹ�������ͨ�Ŷ���ָ�롣

	*/
	virtual ServerSession * createServerSession( const std::string & ipAddr , uint16_t port , const std::string & password ) = 0;
	
	/**ɾ������ͨ��Session
	@remarks
		�ú�����������ɾ��createServerSession����������ͨ�Ŷ���

	@return ��ʾ�Ƿ�ɹ�ɾ����

	*/
	virtual bool destroyServerSession( ServerSession * pSession ) = 0;

	/**��ȡͨ�Ŷ��������
	@remarks
		�ú����������ǻ�ȡͨ�Ŷ����������Ŀ���ǲ������û����д�������������Ӧ����������ĸ����
		����Ĵ�����

	@return ����ͨ�Ŷ��������ָ�롣

	*/
	virtual SessionManager * getSessionManager( ) = 0;
	
	/**���������ļ�����
	@remarks
		�ú��������������ü����������������߾Ϳ��Խ���������ķ��͵�������Ϣ��
	
	@param pListener Ҫ��ӵļ����߶���ָ��

	*/
	virtual void addListener( NetWorkCoreListener * pListener ) = 0;

	/**ɾ��������ļ�����
	@remarks
		�ú�����������ɾ��ָ����������ļ����߶���
	
	@param pListener Ҫɾ���ļ����߶���ָ��

	*/
	virtual void removeListener( NetWorkCoreListener * pListener ) = 0;
};


/** ����ͨ�Ŷ���������
@class ServerSession

@remarks
	��������������ͨ�Ź��ܵĳ���ÿһ��ͨ�Ŷ������һ����ͨ�������ŵ�����ͨ˫��������ͨ���ö���
	�����Ϣ�Ĵ��ݡ�ͨ���û���ĳ����ϲ�Ӧ���������������롣Ϊ�Ժ����չ���ṩ������

@note

@author ���

@date 2009-09-19

*/
class ServerSession
{
public:
	/**��õ�ǰ��ͨ���Ƿ��Ѿ���������
	@remarks
		ֻ�н�����ͨ�ŵĶ���ſ��Ե���sendData�����������ݡ�
	
	@note ���������ڲ�ά����ʹ�����޷��޸ġ�

	@return ���ص�ǰ�Ƿ��Ѿ����ӡ�

	*/
	virtual bool isConnected() = 0;

	/**��õ�ǰ��ͨ�Ŷ���Ľ�ɫ
	@remarks
		�ɱ�����������ӣ����ɹ�����ͨ�Ŷ������ǳ�֮ΪConnector����������Ϊtrue������ǽ���Զ�˵������
		����������ͨ�Ŷ���Connector����Ϊfalse��
	
	@note ���������ڲ�ά����ʹ�����޷��޸ġ�

	@return ���ص�ǰ�����ӽ�ɫ��Ϣ��

	*/
	virtual bool isConnector() = 0;

	/**��õ�ǰͨ�Ŷ����Ψһ���
	@remarks
		һ������ͨ����������������Ļ�Ϊ֮����һ��ΨһID����SessionIndex��
	
	@note ���������ڲ�ά����ʹ�����޷��޸ġ�

	@return ���ص�ǰ��ͨ�Ŷ���ID��

	*/
	virtual uint16_t getSessionIndex() = 0;

	/**��õ�ǰͨ�Ŷ��������
	@remarks
		������Ϊ�ϲ�Ӧ���ṩ��ͨ�Ŷ������Ĺ��ܡ�

	@return ���ص�ǰ��ͨ�Ŷ������͡�

	*/
	virtual SESSION_TYPE getSessionType() = 0;

	/**��õ�ǰͨ�Ŷ��������
	@remarks
	������Ϊ�ϲ�Ӧ���ṩ��ͨ�Ŷ������Ĺ��ܡ�

	@return ���ص�ǰ��ͨ�Ŷ������͡�

	*/
	virtual void setSessionType( SESSION_TYPE type ) = 0;

	/**���ͨ�ŶԷ���IP��ַ
	
	@return �����ַ�����ʽ����ͨ�ŶԷ���ip��ַ������192.168.1.1��

	*/
	virtual const std::string & getRemoteIpAddr() = 0;

	/**���ͨ�ŶԷ���IP��ַ

	@return ���ն����Ʒ�ʽ����ͨ�ŶԷ���ip��ַ��

	*/
	virtual long getRemoteIpAddrBinary() = 0;

	/**���ͨ�ŶԷ��Ķ˿ں�

	@return ����ͨ�ŶԷ��Ķ˿ںš�

	*/
	virtual uint16_t getRemotePort() = 0;
	
	/**���ͨ�ŶԷ�������

	@return ����ͨ�ŶԷ������롣

	*/
	virtual const std::string & getRemotePass() = 0;

	/**��ͨ�ŶԷ�������Ϣ
	@remarks
		�÷���������ͨ�ŶԷ��������ݡ�ֻ�������ӳɹ�������²ſ���ʹ�ø÷�����

	@return ���ط�����Ϣ�Ľ����

	*/
	virtual bool sendData( const MessageData & data ) = 0;

	/**ͨ�Ŷ�����º���
	@remarks
		�ڸú����п��Դ���ά��Ӧ�ò��������ķ��͡�

	*/
	virtual void update() = 0;
	
	///��Ӽ�����
	//virtual void addListener( ServerSessionListener * pListener ) = 0;
	
	//�Ƴ�������
	//virtual void removeListener( ServerSessionListener * pListener ) = 0;
};

/** ����ͨ�Ŷ���������������
@class SessionManager

@remarks
	��������������ͨ�Ŷ���������ĳ��󡣸ó����ṩ������ͨ�Ŷ���ע��ͷ�ע��ķ�����Ŀǰ�Ķ�����ֻ��
	�ɹ����ӵ�ͨ�Ŷ���Żᱻ���뵽����������У����ǶϿ����ӵ�ͨ�Ŷ��󽫻ᱻɾ����

@note

@author ���

@date 2009-09-19

*/
class SessionManager
{
public:

	virtual bool createSession( bool isServer , const std::string & ipAddr , uint16_t port , const std::string & password ) = 0;

	/**ע��ͨ�Ŷ���
	@remarks
		�÷��������������ע��ͨ�Ŷ�������ö���δ�������޷�ע��ɹ���
	
	@param pSession ��ʾͨ�Ŷ���ָ��

	@return ����ע��Ľ����

	*/
	virtual bool registerServerSession( ServerSession * pSession ) = 0;

	/**���ͨ�Ŷ���
	@remarks
		�÷������ڲ�ѯ���е�ͨ�Ŷ��󣬲�ѯ��ʽ����ͨ�ŵ�ΨһID������û�����ӵĶ������޷�ע��ġ�

	@param sessionIndex ��ʾͨ�Ŷ���ID

	@return ���ز�ѯ����ͨ�Ŷ���ָ�롣

	*/
	virtual ServerSession * getServerSession( uint16_t sessionIndex ) = 0;

	/**��ע��ͨ�Ŷ���
	@remarks
		�÷����������������ע��ͨ�Ŷ���

	@param sessionIndex ��ʾͨ�Ŷ���ID

	@return ���ط�ע��Ľ����

	*/
	virtual void unregisterServerSession( uint16_t sessionIndex ) = 0;
	
	/**��õ�ǰͨ�Ŷ������Ŀ
	@remarks
		�÷������ڲ�ѯ��ǰ�������ӵ�ͨ�Ŷ������Ŀ��

	@return ���ز�ѯ����ͨ�Ŷ������Ŀ��

	*/
	virtual uint32_t getServerSessionCount() = 0;
	
	/**��ͨ�ŶԷ�������Ϣ
	@remarks
		�÷���������ͨ�ŶԷ��������ݡ�ֻ�������ӳɹ�������²ſ���ʹ�ø÷�����
	
	@param sessionIndex ��ʾͨ�Ŷ���ID
	@param data ��ʾ���͵�����

	@return ���ط�����Ϣ�Ľ����

	*/
	virtual bool sendData( uint16_t sessionIndex , const MessageData & data ) = 0;

	/**������ͨ�ŶԷ��㲥��Ϣ
	@remarks
		�÷�������������ͨ�ŶԷ����㲥��Ϣ

		@param data ��ʾ���͵�����

	@return ���ط�����Ϣ�Ľ����

	*/
	virtual bool broadSendData( const MessageData & data ) = 0;
	
	/**ͨ�Ŷ�����������º���
	@remarks
		�ڸú����п��Դ����ض���Ӧ�á�

	*/
	virtual void update() = 0;
};

#endif //_NETWORKCOREINTERFACE_HPP_
