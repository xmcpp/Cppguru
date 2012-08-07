#ifndef _NETWORKCOREFACTORY_H_
#define _NETWORKCOREFACTORY_H_

#include "Singleton.h"
#include "NetworkCoreInterface.h"

class NetworkCore;

/** 网络核心对象创建工厂
@class NetworkCoreFactory

@remarks
	这个类负责网络核心对象的创建和销毁。用户可以在创建时选择参数来更换网络核心对象。
	本类是单件类

@note
	目前只支持基于Raknet核心的，未来会增加基于IOCP核心的网络核心对象

@author 徐淼

@date 2009-09-19

*/

class NetworkCoreFactory : public Singleton<NetworkCoreFactory>
{
public:
	///构造函数
	NetworkCoreFactory(){};
	
	///析构函数
	~NetworkCoreFactory();
public:
	///工厂可以创建的核心类型
	enum CORE_TYPE { BASERAKNET , BASEIOCP };
public:
	/**创建网络核心对象
	@remarks
		利用该方法创建指定的网络核心对象，再由网络核心对象负责其它相关对象的创建。对于上层应用
		来说都是透明的，所有对象均基于NetworkCoreinterface中的接口进行操作

	@param type 要创建网络核心对象的类型，目前只有BASERAKNET有效

	@return 返回创建成功的网络核心对象指针
	*/
	NetworkCore * createNetworkCore( CORE_TYPE type );

	/**删除网络核心对象
	@remarks
		利用该方法删除网络核心对象

	@param type 要删除的网络核心对象指针

	*/
	void destroyNetworkCore( NetworkCore * pCore );

private:
	///用于保存已经创建的核心对象，在析构时删除
	std::set<NetworkCore*> m_coreSet;
	typedef std::set<NetworkCore*> coreSet;
};

#endif //_NETWORKCOREFACTORY_H_
