#ifndef __SCRIPTACTIONOBJECT_H__
#define __SCRIPTACTIONOBJECT_H__

#include "ActionObject.h"

class ScriptActionObject : public IActionObject
{
public:
	ScriptActionObject( const std::string & name );
	virtual ~ScriptActionObject();
public:
	virtual bool excute();
	void setActionFunctionName( const std::string & name ){ m_funName = name;}
private:
	std::string m_funName;
};

#endif //__SCRIPTACTIONOBJECT_H__
