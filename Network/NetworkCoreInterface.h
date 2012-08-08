#ifndef _NETWORKCOREINTERFACE_HPP_
#define _NETWORKCOREINTERFACE_HPP_ 

#pragma once

/** 本文件包含网络核心的所有抽象基类

@remarks
	抽象的目的在于希望能够将用户的应用与具体的网络实现隔离开。这样在对网络层的实现进行修改
	时不会影响上层逻辑。目前提供的一套实现是基于Raknet库的。那么基于这样的抽象也可以实现一
	套IOCP的底层，整个网络层的实现变更对上层应用来说完全透明。

@note

@author 徐淼

@date 2009-09-19

*/


#include "BaseDefine.h"


class ServerSession;
class SessionManager;


enum SESSION_TYPE{	INVALID = 0,		///表示无效连接，暂时还没有连通
					UNKNOWN	 ,			///表示有效连接，暂时还不知道身份
					LOGINSERVER  ,		///表示有效连接，对方是Login服务器
					PROXYSERVER   ,		///表示有效连接，对方是代理服务器
					MAPSERVER  ,		///表示有效连接，对方是地图服务器
					MANAGESERVER  ,		///表示有效连接，对方是管理服务器
					DBSERVER  ,			///表示有效连接，对方是数据库服务器
					LOCAL  ,			///
					CLIENT  ,			///表示有效连接，对方是客户端
					USERDEFINE = 100	///留用以后扩展
};


/** 网络核心事件基类
@class NetWorkCoreListener

@remarks
	这个类描述了所有网络核心中可以监听的事件。

@note

@author 徐淼

@date 2009-09-19

*/
/*
class NetWorkCoreListener
{
public:
	//表示有一个连接请求被本机接受
	virtual void onAcceptRemoteConnect( ServerSession * pSession ) = 0;
};*/


/** 网络通信对象基类
@class ServerSessionListener

@remarks
	这个类描述了所有通信对项中可以监听的事件。

@note

@author 徐淼

@date 2009-09-19

*/
class NetWorkCoreListener
{
public:
	///表示本机发出的请求被接受事件
	virtual void onAccepted( ServerSession * pSession ) {};
	
	///表示远端发出的请求被接受事件
	virtual void onConnected( ServerSession * pSession ) {};
	
	///表示与远端连接正常断开连接事件
	virtual void onDisConnected( ServerSession * pSession ) {};
	
	///表示与远端连接非正常断开事件
	virtual void onLostConnected( ServerSession * pSession ) {};
	
	///表示有一个连接请求被本机接受
	virtual void onAcceptRemoteConnect( ServerSession * pSession ){};

	///表示收到远端传送来的数据事件
	virtual void onDataRecv( ServerSession * pSession , const MessageData & data ) {};
};


/** 网络核心功能抽象基类
@class NetworkCore

@remarks
	这个类完成了网络服务的基本功能抽象，是一个抽象基类。

@note

@author 徐淼

@date 2009-09-19

*/

class NetworkCore
{
public:
	/**网络服务初始化函数
	@remarks
		该函数的语义是为整个网络核心做初始化工作，初始化参数由ServerEnv定义。在实现过程中可以按照需要
		选取该结构体中的参数。

	@param env 描述所有的服务器运行时参数，由服务器启动时读取并初始化。

	@return 表示初始化是否成功。

	*/
	virtual bool init( ServerEnv * env ) = 0;

	/**网络服务启动函数
	@remarks
		该函数的语义是基于初始化函数后运行的一个函数，主要负责基于初始化参数启动整个服务器的功能。
	
	@return 表示启动是否成功。

	*/
	virtual bool startService() = 0;

	/**网络服务停止函数
	@remarks
		该函数的语义是负责停止整个服务器服务的功能。

	@return 表示停止是否成功。

	*/
	virtual bool stopService() = 0;

	/**网络服务更新函数
	@remarks
		该函数的语义是为服务器的运行提供一个推动的入口，在该函数中可以处理网络包收取等功能。

	*/
	virtual void update() = 0;

	/**创建网络通信Session
	@remarks
		该函数的语义是基于当前的网络核心创建一个通信Session对象。
	
	@return 返回成功创建的通信对象指针。

	*/
	virtual ServerSession * createServerSession( const std::string & ipAddr , uint16_t port , const std::string & password ) = 0;
	
	/**删除网络通信Session
	@remarks
		该函数的语义是删除createServerSession方法创建的通信对象。

	@return 表示是否成功删除。

	*/
	virtual bool destroyServerSession( ServerSession * pSession ) = 0;

	/**获取通信对象管理器
	@remarks
		该函数的语义是获取通信对象管理器。目的是不允许用户自行创建管理器，而应该由网络核心负责该
		对象的创建。

	@return 返回通信对象管理器指针。

	*/
	virtual SessionManager * getSessionManager( ) = 0;
	
	/**添加网络核心监听者
	@remarks
		该函数的语义是设置监听对象。这样监听者就可以接收网络核心发送的运行消息。
	
	@param pListener 要添加的监听者对象指针

	*/
	virtual void addListener( NetWorkCoreListener * pListener ) = 0;

	/**删除网络核心监听者
	@remarks
		该函数的语义是删除指定的网络核心监听者对象。
	
	@param pListener 要删除的监听者对象指针

	*/
	virtual void removeListener( NetWorkCoreListener * pListener ) = 0;
};


/** 网络通信对象抽象基类
@class ServerSession

@remarks
	这个类完成了网络通信功能的抽象。每一个通信对象基于一个连通的网络信道，连通双方都可以通过该对象
	完成信息的传递。通过该基类的抽象，上层应用与具体的网络层隔离。为以后的扩展性提供帮助。

@note

@author 徐淼

@date 2009-09-19

*/
class ServerSession
{
public:
	/**获得当前的通信是否已经建立起来
	@remarks
		只有建立了通信的对象才可以调用sendData方法发送数据。
	
	@note 该属性由内部维护，使用者无法修改。

	@return 返回当前是否已经连接。

	*/
	virtual bool isConnected() = 0;

	/**获得当前的通信对象的角色
	@remarks
		由本机发起的连接，并成功建立通信对象，我们称之为Connector，即该属性为true。如果是接受远端的请求而
		建立起来的通信对象Connector属性为false。
	
	@note 该属性由内部维护，使用者无法修改。

	@return 返回当前的连接角色信息。

	*/
	virtual bool isConnector() = 0;

	/**获得当前通信对象的唯一编号
	@remarks
		一旦建立通信连接则服务器核心会为之分配一个唯一ID，即SessionIndex。
	
	@note 该属性由内部维护，使用者无法修改。

	@return 返回当前的通信对象ID。

	*/
	virtual uint16_t getSessionIndex() = 0;

	/**获得当前通信对象的类型
	@remarks
		该属性为上层应用提供对通信对象分类的功能。

	@return 返回当前的通信对象类型。

	*/
	virtual SESSION_TYPE getSessionType() = 0;

	/**获得当前通信对象的类型
	@remarks
	该属性为上层应用提供对通信对象分类的功能。

	@return 返回当前的通信对象类型。

	*/
	virtual void setSessionType( SESSION_TYPE type ) = 0;

	/**获得通信对方的IP地址
	
	@return 按照字符串方式返回通信对方的ip地址，例如192.168.1.1。

	*/
	virtual const std::string & getRemoteIpAddr() = 0;

	/**获得通信对方的IP地址

	@return 按照二进制方式返回通信对方的ip地址。

	*/
	virtual long getRemoteIpAddrBinary() = 0;

	/**获得通信对方的端口号

	@return 返回通信对方的端口号。

	*/
	virtual uint16_t getRemotePort() = 0;
	
	/**获得通信对方的密码

	@return 返回通信对方的密码。

	*/
	virtual const std::string & getRemotePass() = 0;

	/**向通信对方发送消息
	@remarks
		该方法用于向通信对方发送数据。只有在连接成功的情况下才可以使用该方法。

	@return 返回发送信息的结果。

	*/
	virtual bool sendData( const MessageData & data ) = 0;

	/**通信对象更新函数
	@remarks
		在该函数中可以处理维持应用层心跳包的发送。

	*/
	virtual void update() = 0;
	
	///添加监听者
	//virtual void addListener( ServerSessionListener * pListener ) = 0;
	
	//移出监听者
	//virtual void removeListener( ServerSessionListener * pListener ) = 0;
};

/** 网络通信对象管理器抽象基类
@class SessionManager

@remarks
	这个类完成了网络通信对象管理器的抽象。该抽象提供了网络通信对象注册和反注册的方法。目前的定义是只有
	成功连接的通信对象才会被加入到这个管理器中，凡是断开连接的通信对象将会被删除。

@note

@author 徐淼

@date 2009-09-19

*/
class SessionManager
{
public:

	virtual bool createSession( bool isServer , const std::string & ipAddr , uint16_t port , const std::string & password ) = 0;

	/**注册通信对象
	@remarks
		该方法用于向管理器注册通信对象。如果该对象未连接则无法注册成功。
	
	@param pSession 表示通信对象指针

	@return 返回注册的结果。

	*/
	virtual bool registerServerSession( ServerSession * pSession ) = 0;

	/**获得通信对象
	@remarks
		该方法用于查询已有的通信对象，查询方式基于通信的唯一ID。所以没有连接的对象是无法注册的。

	@param sessionIndex 表示通信对象ID

	@return 返回查询到的通信对象指针。

	*/
	virtual ServerSession * getServerSession( uint16_t sessionIndex ) = 0;

	/**反注册通信对象
	@remarks
		该方法用于向管理器反注册通信对象。

	@param sessionIndex 表示通信对象ID

	@return 返回反注册的结果。

	*/
	virtual void unregisterServerSession( uint16_t sessionIndex ) = 0;
	
	/**获得当前通信对象的数目
	@remarks
		该方法用于查询当前所有连接的通信对象的数目。

	@return 返回查询到的通信对象的数目。

	*/
	virtual uint32_t getServerSessionCount() = 0;
	
	/**向通信对方发送消息
	@remarks
		该方法用于向通信对方发送数据。只有在连接成功的情况下才可以使用该方法。
	
	@param sessionIndex 表示通信对象ID
	@param data 表示发送的数据

	@return 返回发送信息的结果。

	*/
	virtual bool sendData( uint16_t sessionIndex , const MessageData & data ) = 0;

	/**向所有通信对方广播消息
	@remarks
		该方法用于向所有通信对方发广播消息

		@param data 表示发送的数据

	@return 返回发送信息的结果。

	*/
	virtual bool broadSendData( const MessageData & data ) = 0;
	
	/**通信对象管理器更新函数
	@remarks
		在该函数中可以处理特定的应用。

	*/
	virtual void update() = 0;
};

#endif //_NETWORKCOREINTERFACE_HPP_
