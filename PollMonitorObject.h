/**********************************************************************
��ѯ��ض���

Desc:
	������̳���IMonitorObject�ӿڣ���Ҫ����ѯ�ķ������ж��Ƿ񼤷���
	��ѯͨ������update�ķ������в������ڲ�������onCheck���������ж���
	�÷�������������ʵ�֣����ṩ���ص��ж���ʽ��

Author: ���

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
	virtual void update( float time );
	virtual bool onCheck(){ return false; }
};

#endif //__POOLMONITOROBJECT_H__
