/**********************************************************************
�̻߳���

����boost���߳̿�ʵ�ֵĿ�ƽ̨�̶߳���ͨ���̳и���ʹ����ӵ�ж��߳�
������������onProcess������ʵ�ֹ��ܡ�

Author: ���

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
	/**�����߳� */
	bool beginThread();

	/**ֹͣ�߳� */
	bool endThread();
public:
	/**�����̳߳�ʼ�� */
	virtual void onBegin(){}

	/**�����߳����� */
	virtual void onEnd(){}

	/**�����߳�ִ��
	 *�ú����ᱻ���޴ε��ã����ǵ���endTread������ú�������false
	 *@return ����ú�������false���߳�ִ�н���
	 */
	virtual bool onProcess(){ return true; }
protected:
	void threadProc();
protected:
	boost::thread * m_thread;
	bool m_bStop;
};

#endif //__BOOSTTHREAD_H__
