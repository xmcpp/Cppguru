/**********************************************************************
复合监控对象

Desc:提供组合监控对象的功能。可以将1..n个监控对象复合成一个单独的
监控对象。同时存在两个子类方便使用。
1. ANDMonitorObject 提供当所有子对象都激活时，自身被激活。
2. ORMonitorObject 提供只要有一个子对象被激活时，自身被激活。

Author: 徐淼

Date: 2011.11.30

Update: 
***********************************************************************/

#ifndef __MONITOROBJECTSET_H__
#define __MONITOROBJECTSET_H__

#include <set>
#include "MonitorObject.h"

class MonitorObjectSet : public IMonitorObject , public IMonitorEventListener
{
public:
	MonitorObjectSet(){}
	virtual ~MonitorObjectSet(){}

public:
	/**初始化和清除*/
	virtual bool init();
	virtual bool clear();
	
	/**事件响应函数*/
	virtual void onAlarmActive( IMonitorObject * object );
	virtual void onSilenceActive(  IMonitorObject * object );

public:
	/**管理子MonitorObject*/
	void addMonitorObject( IMonitorObject * object );
	void removeMonitorObject( IMonitorObject * object );
	void clearAllMonitorObject();
protected:
	/**判断是否所有子Monitor对象都符合激活标准
	@remark 该函数是虚函数，需要子类重载，实现自己的判定函数
	@ret true为是，false为否
	*/
	virtual bool isAllActive(){ return false; }
protected:
	std::set<IMonitorObject*> m_monitorObjSet;
	typedef std::set<IMonitorObject*>::iterator monitorObjSetItor;
};


class ANDMonitorObject : public MonitorObjectSet
{
private:
	/**判断是否所有子Monitor对象都符合激活标准
	@remark 实现当所有子Monitor对象都激活时返回True
	@ret true为是，false为否
	*/
	bool isAllActive();
};

class ORMonitorObject : public MonitorObjectSet
{
private:
	/**判断是否所有子Monitor对象都符合激活标准
	@remark 实现当有1个子Monitor对象激活时就返回True
	@ret true为是，false为否
	*/
	bool isAllActive();
};


#endif //__MONITOROBJECTSET_H__

