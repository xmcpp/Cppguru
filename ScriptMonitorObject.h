#ifndef __SCRIPTMONITOROBJECT_H__
#define __SCRIPTMONITOROBJECT_H__

#include "PollMonitorObject.h"

class ScriptMonitorObject : public PollMonitorObject
{
public:
	ScriptMonitorObject(){}
	virtual ~ScriptMonitorObject(){}
public:
	virtual bool onCheck();
	void setCheckFunctionName( const std::string & funName ){ m_funName = funName; }
private:
	std::string m_funName; //��¼�ű���ע���check����������
};

#endif //__SCRIPTMONITOROBJECT_H__
