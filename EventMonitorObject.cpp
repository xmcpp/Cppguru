#include "pch.h"
#include "EventMonitorObject.h"

EventMonitorObject::EventMonitorObject( const std::string & name )
:IMonitorObject(name),m_monitorEventType(0)
{

}

bool EventMonitorObject::init()
{
	return true;
}

bool EventMonitorObject::clear()
{
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