/**********************************************************************
事件监控对象

Desc:
	本对象继承自IMonitorObject接口，主要监控由MessageDispatcher对象
发送的事件。用户可以设置需要监控的事件类型id。当指定类型的事件发生
时，会激发监控对象的状态。
	另外本对象也作为基于事件监控对象的基类而存在。没有把事件接口的
承放在IMonitorObject上，也是考虑不想影响所有的监控对象，因为有些监控
不需要监听事件。

Author: 徐淼

Date: 2011.12.1

Update: 
***********************************************************************/

#ifndef __EVENTMONITOROBJECT_H__
#define __EVENTMONITOROBJECT_H__

#include "MessageDispatcher.h"
#include "MonitorObject.h"

class EventMonitorObject : public IMonitorObject , public IMessageReceiver
{
public:
	EventMonitorObject();
	virtual ~EventMonitorObject(){}
public:
	virtual bool init();
	virtual bool clear();

	void setMonitorEvent( unsigned int messageType ){ m_monitorEventType = messageType; }
protected:
	virtual void ReceiveMessage(unsigned int messageType , ParameterSet& messageParam);

protected:
	unsigned int m_monitorEventType;
};
#endif //__EVENTMONITOROBJECT_H__
