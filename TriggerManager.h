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
