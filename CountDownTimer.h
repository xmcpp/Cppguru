/**********************************************************************
����ʱ��

Desc:����ʱ���ṩ�˴�ָ����ֵ��ʼ����ʱ�Ĺ��ܡ�ͨ�����ü�����
�ӿڣ����Լ���������ʱ���¼������ҿ���ͨ��������õ�ǰ��ʣ��
����ʱ�䡣

Author: ���

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
	/**���õ���ʱ��ʱ��
	@desc �������ʱʱ��δ���ã���ʱ���޷���ʼ������
	@param millisecond ����ʱ����ʱ�䣬��λ����
	*/
	void setCountDownTime( long millisecond );

	/**��ȡ��ʽ����ʣ�൹��ʱʱ��*/
	void getFormatTime( FormatTimeStruct & time );
private:
	void resetTimerData();
private:
	long m_countDownTime;
	long m_lastTime;
	long m_secondTime; //��¼ʱ�������Ƿ�����1����
};

#endif //__COUNTDOWNTIMER_H__
