#include "pch.h"
#include "TimerHelper.h"

TimerHelper::TimerHelper()
{
	reset();
}

TimerHelper::~TimerHelper()
{

}

void TimerHelper::onStart( ITimer * timer )
{
	m_hasStartEvent = true;
	m_eventTimerName = timer->getName();
}

void TimerHelper::onStop( ITimer * timer )
{
	m_hasStopEvent = true;
	m_eventTimerName = timer->getName();
}

void TimerHelper::onPause( ITimer * timer )
{
	m_hasPauseEvent = true;
	m_eventTimerName = timer->getName();
}

void TimerHelper::onResume( ITimer * timer )
{
	m_hasResumeEvent = true;
	m_eventTimerName = timer->getName();
}

void TimerHelper::onSecond( ITimer * timer )
{
	m_hasSecondEvent = true;
	m_eventTimerName = timer->getName();
}

bool TimerHelper::test1()
{
	//ITimer * p = TimerManager::getSingleton().createCountDownTimer( "test" );
	return true;
}

void TimerHelper::reset()
{
	m_hasStartEvent = false;
	m_hasStopEvent = false;
	m_hasPauseEvent = false;
	m_hasResumeEvent = false;
	m_hasSecondEvent = false;

	m_eventTimerName = "";
}