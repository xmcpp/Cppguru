#ifndef __COUNTDOWNTIMER_H__
#define __COUNTDOWNTIMER_H__

#include "TimerObject.h"

class CountDownTimer : public ITimer
{
public:
	CountDownTimer( const std::string & name );
	virtual ~CountDownTimer(){}
public:
	virtual void start();
	virtual void pause();
	virtual void stop();
	virtual void resume();
	virtual void reset();
	virtual void update( float time );
public:
	void setCountDownTime( long millisecond );
	void getFormatTime( FormatTimeStruct & time );
private:
	void resetTimerData();
private:
	long m_countDownTime;
	long m_lastTime;
	long m_secondTime; //记录时间流逝是否满足1秒钟
};

#endif //__COUNTDOWNTIMER_H__
