#ifndef _RAKNETNETWORKCORE_HPP_
#define _RAKNETNETWORKCORE_HPP_ 

#pragma once

#include "NetworkCoreInterface.h"
#include "RakNetTypes.h"
#include "BitStream.h"

struct Packet;
class RakPeerInterface;

/** 基于Raknet的网络核心对象
@class RaknetNetworkCore

@remarks
	这个类从NetworkCore抽象基类继承。是一个基于Raknet库实现的网络层核心对象。

@note
	这个类不能直接创建，只能通过NetworkCoreFactory类创建和删除

@author 徐淼

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
	///初始化
	virtual bool init( ServerEnv * env ) ;
	
	///启动服务
	virtual bool startService() ;
	
	///停止服务
	virtual bool stopService() ;
	
	///更新
	virtual void update() ;
	
	///创建通信对象
	virtual ServerSession * createServerSession( const std::string & ipAddr , uint16_t port , const std::string & password ) ;
	
	///删除通信对象
	virtual bool destroyServerSession( ServerSession * pSession );
	
	///获得通信对象管理器
	virtual SessionManager * getSessionManager( ) ;
	
	///添加监听者
	virtual void addListener( NetWorkCoreListener * pListener );
	
	///删除监听者
	virtual void removeListener( NetWorkCoreListener * pListener );
private:
	/**向指定地址发送数据的函数
	@remarks
		该函数主要基于字符串的ip地址进行操作，速度比较慢。可以调用下一个基于二进制地址的方式调用。

	@return 表示发送是否成功。

	*/
	bool sendData( const std::string & ipAddr , uint16_t port , const MessageData & data );

	//以二进制的地址形式发送数据
	//bool sendData( long ipAddr , uint16_t port , const MessageData & data );

	///处理用户类型的网络包数据
	void processUserPacket( RakNet::Packet * packet );

	///处理网络层类型的包数据
	void processNetworkPacket( RakNet::Packet * packet );

private:
	///表示服务器核心的运行状态
	enum CORE_STATE {	UNREADY ,		///表示未初始化 
						READY ,			///表示以初始化，未运行
						RUNNING ,		///表示以初始化，正在运行
					};
private:
	///保存本地ip
	std::string			m_localIp; 
	
	///保存本地监听端口
	uint16_t			m_localPort; 
	
	///保存登陆密码
	std::string			m_localPassword;
	
	///保存本地最大连接数
	uint16_t			m_localMaxConnectionCount;
	
	///保存本地网络服务轮询时间间隔
	uint32_t			m_localNetworkThreadSleepTime;
	
	//保存内部运行状态
	CORE_STATE			m_coreState;
	
	///保存Raknet服务对象
	RakNet::RakPeerInterface *	m_localServer;
	
	///构造地址对象，用于提供一些操作的速度，不用每次在栈上分配
	RakNet::SystemAddress		m_addr;

	///保存通信对象管理器指针
	SessionManager *	m_sessionMgr;
	
	//保存Raknet流对象，用于向远端发送信息
	RakNet::BitStream	m_bitStream;

	//构造数据对象,用于提高速度，不用每次在栈上分配
	MessageData			m_recvData;

	//用于保存请求连接远端的session的集合，表示还没有连接上的，如果连接上则转移到管理器中
	std::map<unsigned long , ServerSession*>	m_tempSessionMap;
	typedef std::map<unsigned long , ServerSession*> tempSessionMap;
	
	//用于保存作为server的session
	std::map<unsigned long , ServerSession*>	m_serverSessionMap;
	typedef std::map<unsigned long , ServerSession*> serverSessionMap;
	
	//保存监听者指针
	std::set<NetWorkCoreListener*>				m_listenerSet;
	typedef std::set<NetWorkCoreListener*>		listenerSet;

};

#endif //_RAKNETNETWORKCORE_HPP_
