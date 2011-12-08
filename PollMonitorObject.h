/**********************************************************************
��ѯ��ض���

Desc:
	������̳���IMonitorObject�ӿڣ���Ҫ����ѯ�ķ������ж��Ƿ񼤷���
	��ѯͨ������update�ķ������в������ڲ�������onCheck���������ж���
	�÷�������������ʵ�֣����ṩ���ص��ж���ʽ��

Author: ���

Date: 2011.12.2

Update: 
2011.12.8
	����ѯ��ض����Ϊֱ����ϵͳ���¼�����������ѯ���̣�����Ҫ��������
��ѯ�������
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
	virtual bool init();
	virtual bool clear();
	/**������ѯʱ������Ĭ��Ϊ0.1�룬����ʱҲ��ֱ������
	@param time ���ϴ���ѯ֮���ʱ����,��λΪ��
	*/
	void setPollTime( float time ){ m_interVal = time; }
	float getPollTime(){ return m_interVal; }

	/**��ⷽ��
	@remark ÿ����ѯʱ���ø÷�����ִ�о���ļ�⹦�ܡ���Ҫ������������ظù���
	@ret bool �������true����ʾ�����������㡣�������false����ʾ��������������
	*/
	virtual bool onCheck(){ return false; }

	virtual void enable( bool val );
protected:
	virtual void ReceiveMessage(unsigned int messageType , ParameterSet& messageParam);
protected:
	float m_interVal; //��¼��������ѯһ��
	float m_lastTime; //��¼�Ѿ�������
};

#endif //__POOLMONITOROBJECT_H__
