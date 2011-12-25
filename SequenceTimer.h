#ifndef __SEQUENCETIMER_H__
#define __SEQUENCETIMER_H__

#include "TimerObject.h"

class SequenceTimer : public ITimer
{
public:
	SequenceTimer( const std::string & name );
	virtual ~SequenceTimer(){}
public:
	virtual void start();
	virtual void pause();
	virtual void stop();
	virtual void resume();
	virtual void reset();
	virtual void update( float time );
public:
	long getTimeTick(){ return m_lastTime;}
	void getFormatTime( FormatTimeStruct & time ); 
private:
	void resetTimerData();
private:
	long m_lastTime; //记录计时器开始以后经历的时间
	long m_secondTime; //记录时间流逝是否满足1秒钟
};

#endif //__SEQUENCETIMER_H__
