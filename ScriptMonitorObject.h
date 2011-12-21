/**********************************************************************
脚本监控对象

Desc:该脚本对象属于轮训监控对象,是为了方便在脚本中实现检测回调函数
而开发的.就是利用这个类可以允许用脚本来扩展由C++编写的监控对象,即用
脚本实现固定功能的监控对象.

Author: 徐淼

Date: 2011.12.20

Update: 
***********************************************************************/
#ifndef __SCRIPTMONITOROBJECT_H__
#define __SCRIPTMONITOROBJECT_H__

#include "PollMonitorObject.h"

class ScriptMonitorObject : public PollMonitorObject
{
public:
	ScriptMonitorObject(){}
	virtual ~ScriptMonitorObject(){}
public:
	/**轮询对象的回调函数
	@desc 此处内部调用脚本管理器的运行函数，执行注册在本类中的脚本函数来
		  完成监控对象回调功能。
	*/
	virtual bool onCheck();

	/**设置回调脚本的函数名称
	@param funName 函数名称，既可以是全局函数，也可以是table内的函数
	*/
	void setCheckFunctionName( const std::string & funName ){ m_funName = funName; }
private:
	std::string m_funName; //记录脚本中注册的check函数的名称
};

#endif //__SCRIPTMONITOROBJECT_H__
