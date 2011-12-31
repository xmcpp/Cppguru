#ifndef __TESTACTIONOBJECT_H__
#define __TESTACTIONOBJECT_H__

#include "ActionObject.h"

class TestActionObject : public IActionObject
{
public:
	TestActionObject( const std::string & name );
	virtual ~TestActionObject(){}

public:
	virtual bool excute();
	bool getTestState(){ return m_testState; }
	void setTestState( bool val ){ m_testState = val; }
private:
	bool m_testState;
};

#endif //__TESTACTIONOBJECT_H__
