#include "pch.h"
#include "SequenceTimer.h"

SequenceTimer::SequenceTimer( const std::string & name )
:ITimer(name),m_lastTime(0)
{

}

void SequenceTimer::start()
{
	resetTimerData();
	m_timerState = TIMER_RUNNING;
}

void SequenceTimer::pause()
{
	m_timerState = TIMER_PAUSE;
}

void SequenceTimer::stop()
{
	m_timerState = TIMER_STOP;
}

void SequenceTimer::resume()
{
	m_timerState = TIMER_RUNNING;
}

void SequenceTimer::reset()
{
	resetTimerData();
}

void SequenceTimer::update( float time )
{
	if (m_timerState == TIMER_RUNNING)
	{
		m_lastTime += (long)(time * 1000);
	}
}

void SequenceTimer::resetTimerData()
{
	m_lastTime = 0;
	m_timerState = TIMER_STOP;
}

void SequenceTimer::getFormatTime( FormatTimeStruct & time )
{
	timeFormat( m_lastTime , time );
}