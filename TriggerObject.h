/**********************************************************************
触发器对象

Desc:触发器对象将监视器对象和动作器结合,提供相互关联的功能.当监视
器被激活时自动调用关联的动作器完成动作.

Author: 徐淼

Date: 2011.11.28

Update: 
***********************************************************************/
#ifndef __TRIGGEROBJECT_H__
#define __TRIGGEROBJECT_H__

#include "MonitorObject.h"

class IActionObject;
class IMonitorObject;

class TriggerObject : IMonitorEventListener
{
public:
	TriggerObject( const std::string & name );
	virtual ~TriggerObject(){}
public:
	/**设置Monitor对象
	@remark Monitor只能设置一个，如果需要同时关联
			多个，则需要在外面自行构造复合的Monitor对象
	@para object Monitor对象
	*/
	void setMonitorObject( IMonitorObject * object );

	/**设置Monitor激活时对应的Action对象
	@remark 只能设置一个，如果需要同时关联
			多个，则需要在外面自行构造复合的Action对象
	@para object Action对象
	*/
	void setActiveActionObject( IActionObject * object );

	/**设置Monitor反激活时对应的Action对象
	@remark 只能设置一个，如果需要同时关联
			多个，则需要在外面自行构造复合的Action对象
	@para object Action对象
	*/
	void setDeactiveActionObject( IActionObject * object );

	/**主动激发和反激发
	*/
	void trigger();
	void unTrigger();
	
	/**启用/禁用Monitor对象
	@param val true为启用对象，false为禁用对象
	*/
	void enable( bool val ){ m_isEnable = val; }

	/**获取是否启动的状态*/
	bool isEnable() { return m_isEnable; }
	
protected:
	virtual void onAlarmActive();
	virtual void onSilenceActive();
private:
	std::string m_name;
	bool m_isEnable;
	IMonitorObject * m_monitorObject;
	IActionObject * m_activeActionObject;
	IActionObject * m_deactiveActionObject;
};

#endif //__TRIGGEROBJECT_H__
