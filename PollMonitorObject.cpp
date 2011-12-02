#include "pch.h"
#include "PollMonitorObject.h"

void PollMonitorObject::update( float time )
{
	if ( !m_isEnable ) return;

	if ( onCheck() )
		trigger();
	else
		unTrigger();
}
