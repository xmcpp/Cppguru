/**********************************************************************
�¼���ض���

Desc:
	������̳���IMonitorObject�ӿڣ���Ҫ�����MessageDispatcher����
���͵��¼����û�����������Ҫ��ص��¼�����id����ָ�����͵��¼�����
ʱ���ἤ����ض����״̬��
	���Ȿ����Ҳ��Ϊ�����¼���ض���Ļ�������ڡ�û�а��¼��ӿڵ�
�з���IMonitorObject�ϣ�Ҳ�ǿ��ǲ���Ӱ�����еļ�ض�����Ϊ��Щ���
����Ҫ�����¼���

Author: ���

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
