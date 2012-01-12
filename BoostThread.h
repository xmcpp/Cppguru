/**********************************************************************
线程基类

基于boost的线程库实现的跨平台线程对象。通过继承该类使对象拥有多线程
的能力，并在onProcess函数中实现功能。

Author: 徐淼

Date: 2012.1.12

Update: 
***********************************************************************/
#ifndef __BOOSTTHREAD_H__
#define __BOOSTTHREAD_H__

#include "boost/thread/thread.hpp"

class BoostThread
{
public:
	BoostThread();
	virtual ~BoostThread();
public:
	/**启动线程 */
	bool beginThread();

	/**停止线程 */
	bool endThread();
public:
	/**用于线程初始化 */
	virtual void onBegin(){}

	/**用于线程清理 */
	virtual void onEnd(){}

	/**用于线程执行
	 *该函数会被无限次调用，除非调用endTread方法或该函数返回false
	 *@return 如果该函数返回false则线程执行结束
	 */
	virtual bool onProcess(){ return true; }
protected:
	void threadProc();
protected:
	boost::thread * m_thread;
	bool m_bStop;
};

#endif //__BOOSTTHREAD_H__
