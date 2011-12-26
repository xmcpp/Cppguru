#include "pch.h"
#include "SequenceTimer.h"

SequenceTimer::SequenceTimer( const std::string & name )
:ITimer(name),m_lastTime(0),m_secondTime(0)
{

}

void SequenceTimer::start()
{
	if( m_timerState == TIMER_STOP )
	{
		resetTimerData();
		m_timerState = TIMER_RUNNING;
		fireMessage(TIMER_M_START);
	}	
}

void SequenceTimer::pause()
{
	if ( m_timerState == TIMER_RUNNING )
	{
		m_timerState = TIMER_PAUSE;
		fireMessage(TIMER_M_PAUSE);
	}
	
}

void SequenceTimer::stop()
{
	if ( m_timerState == TIMER_RUNNING || m_timerState == TIMER_PAUSE )
	{
		m_timerState = TIMER_STOP;
		fireMessage(TIMER_M_STOP);
	}
}

void SequenceTimer::resume()
{
	if ( m_timerState == TIMER_PAUSE )
	{
		m_timerState = TIMER_RUNNING;
		fireMessage(TIMER_M_RESUME);
	}
}

void SequenceTimer::reset()
{
	resetTimerData();
}

void SequenceTimer::update( float time )
{
	if (m_timerState == TIMER_RUNNING)
	{
		long t = (long)( time * 1000 );
		m_lastTime += t;
		m_secondTime += t;
		if ( m_secondTime >= 1000 )
		{
			fireMessage(TIMER_M_UPDATE);
			m_secondTime -= 1000;
		}
	}
}

void SequenceTimer::resetTimerData()
{
	m_lastTime = 0;
	m_secondTime = 0;
	m_timerState = TIMER_STOP;
}

void SequenceTimer::getFormatTime( FormatTimeStruct & time )
{
	timeFormat( m_lastTime , time );
}

