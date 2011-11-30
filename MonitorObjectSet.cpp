#include "pch.h"
#include "MonitorObjectSet.h"


bool MonitorObjectSet::init()
{
	
	return true;
}

bool MonitorObjectSet::clear()
{
	return true;
}

void MonitorObjectSet::addMonitorObject( IMonitorObject * object )
{
	if( !object ) return;

	m_monitorObjSet.insert( object );

	//监听子监视器对象的事件
	object->addListener( this );
}

void MonitorObjectSet::removeMonitorObject( IMonitorObject * object )
{
	if( !object ) return;

	monitorObjSetItor itor = m_monitorObjSet.find( object );
	if ( itor != m_monitorObjSet.end() )
	{
		object->removeListener( this );
		m_monitorObjSet.erase( itor );
	}
}

void MonitorObjectSet::clearAllMonitorObject()
{
	for ( monitorObjSetItor it = m_monitorObjSet.begin() ; it != m_monitorObjSet.end() ; it++ )
	{
		(*it)->removeListener( this );
	}
	m_monitorObjSet.clear();
}

void MonitorObjectSet::onAlarmActive( IMonitorObject * object )
{
	if ( !m_activeState && isAllActive() )
	{
		//只有当前未激活，并且子Monitor全激活，则发事件
		sendAlarmMsg();
		m_activeState = true;
	}
}

void MonitorObjectSet::onSilenceActive(  IMonitorObject * object )
{
	if ( m_activeState && !isAllActive() )
	{
		//只有当前已经激活，并且子Monitor不是全激活，则发事件
		sendSilenceMsg();
		m_activeState = false;
	}
}

//ANDMonitor对象的实现
bool ANDMonitorObject::isAllActive()
{
	bool ret = true;
	for ( monitorObjSetItor it = m_monitorObjSet.begin() ; it != m_monitorObjSet.end() ; it++ )
	{
		if( !(*it)->isAlarmed() )
		{
			//有一个未激活则返回false
			ret = false;
			break;
		}
	}
	return ret;
}

//ORMonitor对象的实现
bool ORMonitorObject::isAllActive()
{
	bool ret = false;
	for ( monitorObjSetItor it = m_monitorObjSet.begin() ; it != m_monitorObjSet.end() ; it++ )
	{
		if( (*it)->isAlarmed() )
		{
			//有一个激活则返回true
			ret = true;
			break;
		}
	}
	return ret;
}