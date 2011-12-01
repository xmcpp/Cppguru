#include "pch.h"
#include "EventMonitorObject.h"
#include "Singleton.h"

EventMonitorObject::EventMonitorObject()
:m_monitorEventType(0)
{

}

bool EventMonitorObject::init()
{
	MessageDispatcher::getSingleton().addListener( this );
	return true;
}

bool EventMonitorObject::clear()
{
	MessageDispatcher::getSingleton().removeListener( this );
	return true;
}

void EventMonitorObject::ReceiveMessage(unsigned int messageType , const ParameterSet& messageParam)
{
	if ( !m_isEnable ) return;

	if ( m_monitorEventType == messageType )
	{
		trigger();
	}
}