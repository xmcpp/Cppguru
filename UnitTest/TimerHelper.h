#ifndef __TIMERHELPER_H__
#define __TIMERHELPER_H__

#include "TimerObject.h"

class TimerHelper : public TimerListener
{
public:
	TimerHelper();
	~TimerHelper();
public:
	virtual void onStart( ITimer * timer );
	virtual void onStop( ITimer * timer );
	virtual void onPause( ITimer * timer );
	virtual void onResume( ITimer * timer );
	virtual void onSecond( ITimer * timer );
public:
	void reset();
	bool test1();
	bool test2();
public:
	bool m_hasStartEvent;
	bool m_hasStopEvent;
	bool m_hasPauseEvent;
	bool m_hasResumeEvent;
	bool m_hasSecondEvent;
	std::string m_eventTimerName;
};

#endif //__TIMERHELPER_H__
