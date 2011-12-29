/**********************************************************************
����������

Desc:���������󽫼���������Ͷ��������,�ṩ�໥�����Ĺ���.������
��������ʱ�Զ����ù����Ķ�������ɶ���.

Author: ���

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
	/**����Monitor����
	@remark Monitorֻ������һ���������Ҫͬʱ����
			���������Ҫ���������й��츴�ϵ�Monitor����
	@para object Monitor����
	*/
	void setMonitorObject( IMonitorObject * object );

	/**����Monitor����ʱ��Ӧ��Action����
	@remark ֻ������һ���������Ҫͬʱ����
			���������Ҫ���������й��츴�ϵ�Action����
	@para object Action����
	*/
	void setActiveActionObject( IActionObject * object );

	/**����Monitor������ʱ��Ӧ��Action����
	@remark ֻ������һ���������Ҫͬʱ����
			���������Ҫ���������й��츴�ϵ�Action����
	@para object Action����
	*/
	void setDeactiveActionObject( IActionObject * object );

	/**���������ͷ�����
	*/
	void trigger();
	void unTrigger();
	
	/**����/����Monitor����
	@param val trueΪ���ö���falseΪ���ö���
	*/
	void enable( bool val ){ m_isEnable = val; }

	/**��ȡ�Ƿ�������״̬*/
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
