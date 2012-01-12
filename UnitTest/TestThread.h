#ifndef __TESTTHREAD_H__
#define __TESTTHREAD_H__

#include "BoostThread.h"

class TestThread : public BoostThread
{
public:
	TestThread();
	virtual ~TestThread();

public:
	void onBegin();
	bool onProcess();
	void onEnd();
	int getValue(){ return m_value; }
private:
	int m_value;
};

#endif //__TESTTHREAD_H__
