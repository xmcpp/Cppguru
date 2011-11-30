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

	//�����Ӽ�����������¼�
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
		//ֻ�е�ǰδ���������Monitorȫ������¼�
		sendAlarmMsg();
		m_activeState = true;
	}
}

void MonitorObjectSet::onSilenceActive(  IMonitorObject * object )
{
	if ( m_activeState && !isAllActive() )
	{
		//ֻ�е�ǰ�Ѿ����������Monitor����ȫ������¼�
		sendSilenceMsg();
		m_activeState = false;
	}
}

//ANDMonitor�����ʵ��
bool ANDMonitorObject::isAllActive()
{
	bool ret = true;
	for ( monitorObjSetItor it = m_monitorObjSet.begin() ; it != m_monitorObjSet.end() ; it++ )
	{
		if( !(*it)->isAlarmed() )
		{
			//��һ��δ�����򷵻�false
			ret = false;
			break;
		}
	}
	return ret;
}

//ORMonitor�����ʵ��
bool ORMonitorObject::isAllActive()
{
	bool ret = false;
	for ( monitorObjSetItor it = m_monitorObjSet.begin() ; it != m_monitorObjSet.end() ; it++ )
	{
		if( (*it)->isAlarmed() )
		{
			//��һ�������򷵻�true
			ret = true;
			break;
		}
	}
	return ret;
}