/**********************************************************************
��ѯ��ض��������

Desc:������ѯ���󣬵�������.�ڲ�����������Ϣ��ʹ��ʱ����Ҫ������÷�����
	 ������Ϣʵ����ѯ���ڲ�������Ϣ�����͵�MD_TIME_FRAMETICK
	 �¼������¼�ÿ֡����һ�������Խ��ո��¼����ƶ���ѯ������

Author: ���

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
	/**������Ҫ��ѯ�ļ��������*/
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
