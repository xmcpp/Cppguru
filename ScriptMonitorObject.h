/**********************************************************************
�ű���ض���

Desc:�ýű�����������ѵ��ض���,��Ϊ�˷����ڽű���ʵ�ּ��ص�����
��������.���������������������ýű�����չ��C++��д�ļ�ض���,����
�ű�ʵ�̶ֹ����ܵļ�ض���.

Author: ���

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
	/**��ѯ����Ļص�����
	@desc �˴��ڲ����ýű������������к�����ִ��ע���ڱ����еĽű�������
		  ��ɼ�ض���ص����ܡ�
	*/
	virtual bool onCheck();

	/**���ûص��ű��ĺ�������
	@param funName �������ƣ��ȿ�����ȫ�ֺ�����Ҳ������table�ڵĺ���
	*/
	void setCheckFunctionName( const std::string & funName ){ m_funName = funName; }
private:
	std::string m_funName; //��¼�ű���ע���check����������
};

#endif //__SCRIPTMONITOROBJECT_H__
