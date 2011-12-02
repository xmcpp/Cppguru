/**********************************************************************
监控对象接口

Desc:监控对象接口是监控对象的基类,提供了监控对象的基本行为定义.
同时还提供了监控对象监听器接口

Author: 徐淼

Date: 2011.11.28

Update: 
***********************************************************************/

#ifndef __MONITOROBJECT_H__
#define __MONITOROBJECT_H__

#include <set>

class IMonitorObject;

/**monitor的事件监听接口
*
*/
class IMonitorEventListener
{
public:
	/**激活事件
	@remark 当被激活时发出该事件
	@param object 发出事件的对象指针，方便接收者分析事件来源 
	*/
	virtual void onAlarmActive( IMonitorObject * object ){}

	/**反激活事件
	@remark 当被反激活时发出该事件
	@param object 发出事件的对象指针，方便接收者分析事件来源 
	*/
	virtual void onSilenceActive(  IMonitorObject * object ){}
};

/**monitor的对象接口
*
*/
class IMonitorObject 
{
public:
	/**构造函数
	@param name 监控对象的名称,默认为空
	@param bAutoReset 是否是自动复位对象，默认为false
	*/
	IMonitorObject( const std::string & name = "" , bool bAutoReset = false );
	virtual ~IMonitorObject(){}

public:
	/**初始化和清除*/
	virtual bool init(){ return true;}
	virtual bool clear(){ return true;}
	
	/**设置和获得名称*/
	const std::string & getName(){ return m_name; }
	void setName( const std::string & name ){ m_name = name; }
	
	/**设置和获得是否自动复位*/
	bool isAutoReset(){ return m_isAutoReset; }
	void setAutoReset( bool val ){ m_isAutoReset = val; }

	/**启用/禁用Monitor对象
	@param val true为启用对象，false为禁用对象
	*/
	virtual void enable( bool val ){ m_isEnable = val; }
	
	/**获取是否启动的状态*/
	virtual bool isEnable() { return m_isEnable; }
	
	/**获取是否激活的状态
	@remark 激活和未激活状态是互斥的，状态只能在这两个之中变化
	*/
	virtual bool isAlarmed(){ return m_activeState; }
	
	/**获取是否未激活的状态*/
	virtual bool isSilence(){ return !m_activeState; }
	
	/**激活和反激活Monitor对象
	@remark 该方法可以绕过监控条件，强制激活或反激活Monitor的对象。
	该方法会自动设置对象状态，具体状态可以从isAlarmed和isSilence方法获得。
	*/
	virtual void trigger();
	virtual void unTrigger();

	/**对象监听者管理*/
	void addListener( IMonitorEventListener * listener );
	void removeListener( IMonitorEventListener * listener );
	void clearAllListener();
protected:
	/**向所有监听者发送事件*/
	void sendAlarmMsg();
	void sendSilenceMsg();
protected:
	std::string m_name;
	std::set<IMonitorEventListener*> m_listenerSet;
	typedef std::set<IMonitorEventListener*>::const_iterator listenerSetItor;
	bool m_activeState; //是否激活的状态位
	bool m_isEnable;	//是否启用
	bool m_isAutoReset; //是否自动复位，即是否有激活后立即自动复位的功能,默认为false，不自动复位
};


#endif //__MONITOROBJECT_H__
