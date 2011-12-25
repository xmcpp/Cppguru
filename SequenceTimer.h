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
	long m_lastTime; //��¼��ʱ����ʼ�Ժ�����ʱ��
	long m_secondTime; //��¼ʱ�������Ƿ�����1����
};

#endif //__SEQUENCETIMER_H__
