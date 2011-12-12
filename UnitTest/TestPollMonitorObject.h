#ifndef __TESTPOLLMONITOROBJECT_H__
#define __TESTPOLLMONITOROBJECT_H__

#include "PollMonitorObject.h"

class TestPollMonitorObject : public PollMonitorObject
{
public:
	TestPollMonitorObject();
	virtual bool onCheck();
	
	void cheat();
private:
	bool m_isTrue;
};


#endif //__TESTPOLLMONITOROBJECT_H__
