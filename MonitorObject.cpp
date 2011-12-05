#include "pch.h"
#include "MonitorObject.h"

IMonitorObject::IMonitorObject( const std::string & name , bool bAutoReset )
:m_name(name),m_activeState(false),m_isEnable(false),m_isAutoReset(bAutoReset)
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
		m_activeState = true;
		sendAlarmMsg();
		
		//是否自动复位
		if ( m_isAutoReset )
		{
			unTrigger(); //执行复位操作
		}
	}
}

void IMonitorObject::unTrigger()
{
	if( !m_isEnable ) return;

	if( m_activeState )
	{
		m_activeState = false;
		sendSilenceMsg();
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