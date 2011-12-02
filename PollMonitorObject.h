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
	PollMonitorObject(){}
	virtual ~PollMonitorObject(){}

public:
	/**轮询方法，每次轮询需要调用该方法
	@param time 与上次轮询之间的时间间隔
	*/
	virtual void update( float time );

	/**检测方法
	@remark 每次轮询时调用该方法来执行具体的监测功能。需要具体的子类重载该功能
	@ret bool 如果返回true，表示监测的条件满足。如果返回false，表示监测的条件不满足
	*/
	virtual bool onCheck(){ return false; }
};

#endif //__POOLMONITOROBJECT_H__
