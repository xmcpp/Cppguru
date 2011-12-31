/**********************************************************************
触发器对象管理器

Desc:

Author: 徐淼

Date: 2011.12.31

Update: 
***********************************************************************/

#ifndef __POLLMONITORMANAGER_H__
#define __POLLMONITORMANAGER_H__

#include "MapManager.h"
#include "Singleton.h"
#include "TriggerObject.h"
#include "MonitorObjectManager.h"
#include "ActionObjectManager.h"


class TriggerManager : public Singleton<TriggerManager> , public MapManager<TriggerObject>
{
public:
	TriggerManager();
	virtual ~TriggerManager();
public:
	void initTriggerSystem();
	void uninitTriggerSystem();
	
	TriggerObject * createTrigger( const std::string & name );
	TriggerObject * getTrigger( const std::string & name );
	bool destroyTrigger( const std::string & name );
	
	ActionObjectManager * getActionObjectManager(){ return m_actObjMgr; }
	MonitorObjectManager * getMonitorObjectManager(){ return m_monitorObjMgr; }
private:
	ActionObjectManager * m_actObjMgr;
	MonitorObjectManager * m_monitorObjMgr;
	bool m_bInit;
};

#endif //__POLLMONITORMANAGER_H__
