/**********************************************************************
顺序定时器

Desc:顺序定时器提供了从0开始计时的功能。通过设置监听者接口，可以
监听各个定时器事件，并且可以通过方法获得当前已经流逝了多少时间。

Author: 徐淼

Date: 2011.12.22

Update: 
***********************************************************************/
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
	/**获得当前流逝的时间总数*/
	long getTimeTick(){ return m_lastTime;}

	/**获取当前格式化以后的流逝时间总数*/
	void getFormatTime( FormatTimeStruct & time );
private:
	void resetTimerData();
private:
	long m_lastTime; //记录计时器开始以后经历的时间
	long m_secondTime; //记录时间流逝是否满足1秒钟
};

#endif //__SEQUENCETIMER_H__
