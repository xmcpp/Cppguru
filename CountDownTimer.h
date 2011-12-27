/**********************************************************************
倒序时器

Desc:倒序定时器提供了从指定数值开始倒计时的功能。通过设置监听者
接口，可以监听各个定时器事件，并且可以通过方法获得当前还剩余
多少时间。

Author: 徐淼

Date: 2011.12.22

Update: 
***********************************************************************/
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
	/**设置倒计时的时间
	@desc 如果倒计时时间未设置，则定时器无法开始工作。
	@param millisecond 倒计时的总时间，单位毫秒
	*/
	void setCountDownTime( long millisecond );

	/**获取格式化的剩余倒计时时间*/
	void getFormatTime( FormatTimeStruct & time );
private:
	void resetTimerData();
private:
	long m_countDownTime;
	long m_lastTime;
	long m_secondTime; //记录时间流逝是否满足1秒钟
};

#endif //__COUNTDOWNTIMER_H__
