#include "pch.h"
#include "TimerObject.h"

ITimer::ITimer( const std::string & name )
:m_name(name),m_timerState(TIMER_STOP)
{
	
}

ITimer::~ITimer()
{
	
}

void ITimer::addListener( TimerListener * listener )
{
	m_timerSet.insert( listener );
}

void  ITimer::removeListener( TimerListener * listener )
{
	timerSetItor it = m_timerSet.find( listener );
	if( it != m_timerSet.end() )
	{
		m_timerSet.erase( it );
	}
}

void ITimer::timeFormat( unsigned long time , FormatTimeStruct & data )
{
	data.m_hours = time / 3600000;
	time = time - ( data.m_hours * 3600000 );

	data.m_minutes = time / 60000;
	time = time - ( data.m_minutes * 60000 );

	data.m_seconds = time / 1000;
	time = time - ( data.m_seconds * 1000 );

	data.m_millSeconds = time;
}