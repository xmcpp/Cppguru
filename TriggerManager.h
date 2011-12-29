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

#include "MapManager.h"
#include "Singleton.h"
class TriggerObject;
class ActionObjectManager;

class TriggerManager : public Singleton<TriggerManager> , public MapManager<TriggerManager>
{
public:
	TriggerManager();
	virtual ~TriggerManager();
public:
	void initTriggerSystem();
	void uninitTriggerSystem();
	
	TriggerObject * createTrigger( const std::string & name );
	TriggerObject * getTrigger( const std::string & name );
	void destroyTrigger( const std::string & name );
	
	ActionObjectManager * getActionObjectManager(){ return m_actObjMgr; }

private:
	ActionObjectManager * m_actObjMgr;
};

#endif //__POLLMONITORMANAGER_H__
