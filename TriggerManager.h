/**********************************************************************
轮询监控对象管理器

Desc:管理轮询对象，单件对象.内部处理所有信息，使用时不需要额外调用方法。
	 利用消息实现轮询，内部接收消息对象发送的MD_TIME_FRAMETICK
	 事件，该事件每帧发送一个，所以接收该事件来推动轮询操作。

Author: 徐淼

Date: 2011.12.2

Update: 
***********************************************************************/

#ifndef __POLLMONITORMANAGER_H__
#define __POLLMONITORMANAGER_H__

#include "MessageDispatcher.h"
#include "EventMonitorObject.h"

class PollMonitorObject;

class PollMonitorManager : public Singleton<PollMonitorManager> , public IMessageReceiver
{
public:
	PollMonitorManager();
	virtual ~PollMonitorManager();
public:
	/**管理需要轮询的监控器对象*/
	void addPollMonitor( PollMonitorObject * object );
	void removePollMonitor( PollMonitorObject * object );
	void clearAllPollMonitor();
protected:
	void update( float time );
	virtual void ReceiveMessage(unsigned int messageType , ParameterSet& messageParam);

private:
	std::set<PollMonitorObject*> m_set;
	typedef std::set<PollMonitorObject*>::iterator setItor;
};

#endif //__POLLMONITORMANAGER_H__
