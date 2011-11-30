#include "pch.h"
#include "MonitorObject.h"

IMonitorObject::IMonitorObject( const std::string & name )
:m_name(name),m_activeState(false),m_isEnable(false)
{

}

void IMonitorObject::addListener( IMonitorEventListener * listener )
{
	m_listenerSet.insert(listener);
}

void IMonitorObject::removeListener( IMonitorEventListener * listener )
{
	listenerSetItor itor = m_listenerSet.find( listener );
	if ( itor != m_listenerSet.end() )
	{
		m_listenerSet.erase( itor );
	}
}

void IMonitorObject::clearAllListener()
{
	m_listenerSet.clear();
}

void IMonitorObject::trigger()
{
	if( !m_isEnable ) return;
	
	if( !m_activeState )
	{
		sendAlarmMsg();
		m_activeState = true;
	}
}

void IMonitorObject::unTrigger()
{
	if( !m_isEnable ) return;

	if( m_activeState )
	{
		sendSilenceMsg();
		m_activeState = false;
	}
}

void IMonitorObject::sendAlarmMsg()
{
	for ( listenerSetItor itor = m_listenerSet.begin() ; itor != m_listenerSet.end() ; itor++ )
	{
		(*itor)->onAlarmActive( this );
	}
}

void IMonitorObject::sendSilenceMsg()
{
	for ( listenerSetItor itor = m_listenerSet.begin() ; itor != m_listenerSet.end() ; itor++ )
	{
		(*itor)->onSilenceActive( this );
	}
}