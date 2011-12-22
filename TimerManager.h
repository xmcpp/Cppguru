#ifndef __TIMERMANAGER_H__
#define __TIMERMANAGER_H__

#include "Singleton.h"

class EventMonitorObject;
class CountDownTimer;
class SequenceTimer;
class TimerManager : public Singleton<TimerManager>
{
public:
	TimerManager();
	~TimerManager();
public:
	CountDownTimer * createCountDownTimer( const std::string & name );
	SequenceTimer * createSequenceTimer( const std::string & name );
private:
	EventMonitorObject * m_eventMonitorObj;
};

#endif //__TIMERMANAGER_H__
