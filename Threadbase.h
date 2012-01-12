#ifndef __THREADBASE_H__
#define __THREADBASE_H__

#include <windows.h>

class ThreadBase
{
public:		
	/// 默认构造函数
	ThreadBase();
	/// 默认析构函数
	virtual ~ThreadBase();

public:		
	// false: 暂不运行，用 ResumeThread() 运行
	bool createThread(bool bRun = true);	

	// return false: 失败
	bool resumeThread();			

	// 通知子线程关闭，并阻塞 nMilliseconds 毫秒。返回true: 线程关闭成功
	bool closeThread(long nMilliseconds = 0);
    
	bool suspendThread();
	
// 派生用
protected:	
	virtual	void	onInit() { }
	virtual bool	onProcess() { return true;};		
	virtual void	onDestroy() { }

// 内部使用
private:	
	// 检查关闭线程事件是否触发。用于 ThreadProc() 函数调用
	bool	isCloseEvent(long nMilliseconds = 0);		
	DWORD	threadProc();
	bool	isCreated() { return (m_hThread != NULL); }

protected:
	HANDLE		m_hThread;
	HANDLE		m_hCloseThreadEvent;

	
private:
	static DWORD WINAPI trueThreadProc(LPVOID pParam);
};

#endif //__THREADBASE_H__
