/**********************************************************************
轮询监控对象

Desc:
	本对象继承自IMonitorObject接口，主要由轮询的方法来判断是否激发。
	轮询通过调用update的方法进行操作。内部将调用onCheck方法进行判定。
	该方法可由子类来实现，并提供独特的判定方式。

Author: 徐淼

Date: 2011.12.2

Update: 
***********************************************************************/

#ifndef __POOLMONITOROBJECT_H__
#define __POOLMONITOROBJECT_H__

#include "MonitorObject.h"

class PollMonitorObject : public IMonitorObject
{
public:
	PollMonitorObject( float defaultPollTime = 0.1f )
		:m_interVal(defaultPollTime),m_lastTime(0.0f)
	{}
	virtual ~PollMonitorObject(){}

public:
	/**设置轮询时间间隔，默认为0.1秒，构造时也可直接设置
	@param time 与上次轮询之间的时间间隔,单位为秒
	*/
	void setPollTime( float time ){ m_interVal = time; }
	float getPollTime(){ return m_interVal; }

	/**轮询方法，每次轮询需要调用该方法
	@param time 与上次轮询之间的时间间隔,单位为秒
	*/
	virtual void update( float time );

	/**检测方法
	@remark 每次轮询时调用该方法来执行具体的监测功能。需要具体的子类重载该功能
	@ret bool 如果返回true，表示监测的条件满足。如果返回false，表示监测的条件不满足
	*/
	virtual bool onCheck(){ return false; }

	virtual void enable( bool val );
protected:
	float m_interVal; //记录间隔多久轮询一次
	float m_lastTime; //记录已经间隔多久
};

#endif //__POOLMONITOROBJECT_H__
