/**********************************************************************
Monitor对象管理器

Desc:Monitor对象管理器管理已经创建的所有动作对象,不负责创建但可以负责删除
Author: 徐淼

Date: 2011.12.31

Update: 
***********************************************************************/
#ifndef __MONITOROBJECTMANAGER_H__
#define __MONITOROBJECTMANAGER_H__

#include "MapManager.h"

class IMonitorObject;
class MonitorObjectManager : public MapManager<IMonitorObject>
{
public:
	MonitorObjectManager(){}
	~MonitorObjectManager(){}
public:
	bool addMonitorObject( IMonitorObject * object );
	IMonitorObject * getMonitorObject( const std::string & name );
	bool removeMonitorObject( IMonitorObject * object , bool bDestory = false );
	bool removeMonitorObject( const std::string & name , bool bDestory = false );
	void removeAllMonitorObject( bool bDestory = false );
};

#endif //__MONITOROBJECTMANAGER_H__
