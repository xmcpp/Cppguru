#ifndef _MESSAGEQUENEPROCESSOR_HPP_
#define _MESSAGEQUENEPROCESSOR_HPP_ 

#pragma once

#include "ThreadBase.h"
#include "BaseDefine.h"
#include "RingBuffer.h"

/** 消息处理队列线程类
@class MessageQueneProcessor

@remarks
	这个类从ThreadBase继承，实现服务器框架中消息分发的工作线程。

@note
	本类中的方法是线程安全的。

@author 徐淼

@date 2009-09-15

*/

class MessageQueneProcessor : public ThreadBase
{
public:
	///默认构造函数
	MessageQueneProcessor();

	///默认析构函数
	virtual ~MessageQueneProcessor(); 

public:
	/**抽象事件接口
	@remarks
		消息处理器从队列中取出消息后会调用该接口中的onMessageProcess方法，参数是事件对象的常引用
	*/
	class QueneProcessorListener
	{
	public:
		virtual bool onMessageProcess( const MessageData & data ) = 0;
	};

public:
	/**启动事件处理器
	@remarks
		启动消息处理器，通过参数控制是否立刻开始工作
	
	@param bRun 表示是否立刻运行 true为立刻运行，false为启动后暂停
	*/
	bool startProcessor( bool bRun = true );

	/**恢复消息处理器运行
	@remarks
		恢复消息处理器运行，一般在消息处理器暂停后可以调用本方法恢复运行
	*/
	bool resumeProcessor();

	/**恢复消息处理器运行
	@remarks
		暂停消息处理器运行，只能在处理完一个消息后暂停。调用本方法后会纪录一个
		状态，在处理完当前消息后处理器进入暂停状态。可以通过调用resumeProcessor
		恢复运行状态
	*/
	bool suspendProcessor();

	/**停止消息处理器运行
	@remarks
		停止消息处理器运行，该方法调用后将停止整个处理流程，必须在调用startProcessor方法
		重新启动。停止方法会在处理完一个消息后生效，如果消息队列中还有其它消息则会被丢弃
	*/
	bool stopProcessor();
	
	/**向消息队列尾部添加一个消息
	@remarks
		本方法在实现时将会对传入的数据做深拷贝操作

	@param data 等待处理的消息对象的引用
	@param pCurrentMsgCount 类型为指针，返回内容为当前消息缓冲区中有多少剩余未处理的消息，数目上包含当前
							方法添加的一个，除非返回false。
	*/
	bool addMessage( const MessageData & data , uint32_t * pCurrentMsgCount );
	
	/**获得当前未处理消息的数目
	*/
	int32_t getMessageCount();

	/**设置回调对象地址
	*/
	void setQueneProcessorListener( QueneProcessorListener * pListener );

private:
	
	/**主处理函数，内部使用，由线程调用
	*/
	virtual bool onProcess();
private:
	///消息队列的定义
	std::deque<MessageData> m_msgQuene;
	
	///同步对象关键区的定义
	CRITICAL_SECTION m_section;

	///同步对象信号灯的定义,这个信号灯用于表示当前消息队列中消息的数目，初始化为0，表示没有消息
	///当执行了添加消息后增加一个值
	HANDLE m_semaphore;

	///回调对象地址定义
	QueneProcessorListener * m_listener;

	//数据区对象
	RingBuffer				m_msgDataBuff;
};

#endif //_MESSAGEQUENEPROCESSOR_HPP_
