#include "pch.h"
#include "TriggerObject.h"
#include "ActionObject.h"

TriggerObject::TriggerObject( const std::string & name )
:m_isEnable(false),m_monitorObject(NULL),m_activeActionObject(NULL),m_deactiveActionObject(NULL),
m_name(name)
{

}

void TriggerObject::setMonitorObject( IMonitorObject * object )
{
	if ( m_monitorObject )
	{
		//如果之前绑定过对象，则先清除
		m_monitorObject->removeListener( this );
	}
	
	m_monitorObject = object;
	m_monitorObject->addListener( this );
}

void TriggerObject::setActiveActionObject( IActionObject * object )
{
	m_activeActionObject = object;
}

void TriggerObject::setDeactiveActionObject( IActionObject * object )
{
	m_deactiveActionObject = object;
}

void TriggerObject::onAlarmActive()
{
	if ( m_isEnable && m_activeActionObject )
	{
		m_activeActionObject->excute();
	}
}

void TriggerObject::onSilenceActive()
{
	if ( m_isEnable && m_deactiveActionObject )
	{
		m_deactiveActionObject->excute();
	}
}

void TriggerObject::trigger()
{
	if ( !m_isEnable ) { return; }
	
	//手动触发
	onAlarmActive();
}

void TriggerObject::unTrigger()
{
	if ( !m_isEnable ) { return; }
	
	//手动触发
	onSilenceActive();
}