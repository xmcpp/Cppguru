/***********************************
消息调度器

Author: 苗琳

Date: 2010.12.22

Update: 
************************************/


#ifndef MessageDispatcher_h
#define MessageDispatcher_h

#include "ParameterSet.h"
#include "ListenerManager.h"
#include "Singleton.h"
#include "MessageTypeDef.h"


/** 消息接收器抽象接口
@remark
	隔离消息接收方与消息调度器的关系,消息接收方有可能来自于脚本系统，
也有可能来自于C++中的某些模块，消息调度器通过该接口统一调度事件。
*/
class IMessageReceiver
{
public:
	/** 接收消息接口
	@param messageType 消息类型标识
	@param messageParam 消息参数集对象
	*/
	virtual void ReceiveMessage(unsigned int messageType , const ParameterSet& messageParam){};
};



/** 消息调度器
@remark
	负责消息的发送，调度，轮询等任务
所有需要收消息的模块都需要继承IMessageReceiver接口，
并将自己指针通过addListener(this)注册到该类
*/
class MessageDispatcher : public ListenerManager<IMessageReceiver> , public Singleton<MessageDispatcher>
{
public:
	MessageDispatcher(void);
	~MessageDispatcher(void);

	/** 发送消息
	@remark 同步模式，立即发送给每个消息接收器
	@param messageType 消息类型标识
	@param messageParam 消息参数集对象
	*/
	void SendMessage(unsigned int messageType , const ParameterSet& messageParam);

	/** 投递消息
	@remark 异步模式,只将消息投递到队列中，在每桢更新的时候在发送给每个消息接收器
	@param messageType 消息类型标识
	@param messageParam 消息参数集对象
	*/
	void PostMessage(unsigned int messageType , const ParameterSet& messageParam);

	void Update(float timeSinceLastFrame);

private:
	/** 消息结构体
	@remark 内部维护的消息结构体,主要记录消息的全部信息保存在列表中等待处理
	*/
	class MessageInfo
	{
	public:
		///消息类型标识
		unsigned int type;
		///消息参数集对象
		ParameterSet param;
	};

	///消息队列
	std::list<MessageInfo> mMessageList;

};

#endif //MessageDispatcher_h