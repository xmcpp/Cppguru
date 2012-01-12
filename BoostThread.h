#ifndef __BOOSTTHREAD_H__
#define __BOOSTTHREAD_H__

#include "boost/thread/thread.hpp"

class BoostThread
{
public:
	BoostThread();
	~BoostThread();
public:
	bool beginThread();
	bool endThread();
	
protected:
	void threadProc();
protected:
	boost::thread * m_thread;
	bool m_isRunning;
};

#endif //__BOOSTTHREAD_H__
