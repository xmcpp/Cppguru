#include "pch.h"
#include "CountDownTimer.h"

CountDownTimer::CountDownTimer( const std::string & name )
:ITimer(name),m_countDownTime(0)
{

}

void CountDownTimer::start()
{
	if ( m_countDownTime > 0 && m_timerState == TIMER_STOP )
	{
		resetTimerData();
		m_timerState = TIMER_RUNNING;
		fireMessage(TIMER_M_START);
	}
	
}

void CountDownTimer::pause()
{
	if( m_timerState == TIMER_RUNNING )
	{
		m_timerState = TIMER_PAUSE;
		fireMessage(TIMER_M_PAUSE);
	}	
}

void CountDownTimer::stop()
{
	if( m_timerState == TIMER_RUNNING || m_timerState == TIMER_PAUSE )
	{
		m_timerState = TIMER_STOP;
		fireMessage(TIMER_M_STOP);
	}
}

void CountDownTimer::resume()
{
	if( m_timerState == TIMER_PAUSE )
	{
		m_timerState = TIMER_RUNNING;
		fireMessage(TIMER_M_RESUME);
	}
}

void CountDownTimer::reset()
{
	resetTimerData();
}

void CountDownTimer::update( float time )
{
	if (m_timerState == TIMER_RUNNING)
	{
		long t = (long)( time * 1000 );
		m_lastTime += t;
		if ( m_countDownTime - m_lastTime <= 0 )
		{
			//倒计时完成
			fireMessage( TIMER_M_STOP );
			return;
		}
		m_secondTime += t;
		if ( m_secondTime >= 1000 )
		{
			fireMessage(TIMER_M_UPDATE);
			m_secondTime -= 1000;
		}
	}
}

void CountDownTimer::setCountDownTime( long millisecond )
{
	//只有在停止时才可以设置时间
	if ( m_timerState == TIMER_STOP )
	{
		m_countDownTime = millisecond;
	}
}

void CountDownTimer::getFormatTime( FormatTimeStruct & time )
{
	long result = m_countDownTime - m_lastTime;
	timeFormat( (result>0)?result:0 , time );
}

void CountDownTimer::resetTimerData()
{
	m_lastTime = 0;
	m_secondTime = 0;
	m_timerState = TIMER_STOP;
}