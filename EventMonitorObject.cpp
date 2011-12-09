#include "pch.h"
#include "EventMonitorObject.h"

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

void EventMonitorObject::ReceiveMessage(unsigned int messageType , ParameterSet& messageParam)
{
	IMonitorObject::ReceiveMessage( messageType , messageParam );

	if ( !m_isEnable ) return;

	if ( m_monitorEventType == messageType )
	{
		trigger();
	}
}