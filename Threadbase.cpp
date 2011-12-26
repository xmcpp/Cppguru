#include "pch.h"
#include "ThreadBase.h"

//*********************************************************
//default constructor for class CThread
//*********************************************************
ThreadBase::ThreadBase()
{
	m_hThread		= NULL;
	m_hCloseThreadEvent	= NULL;
}

//*********************************************************
//destructor for class CObject
//*********************************************************
ThreadBase::~ThreadBase()
{
	if (m_hThread) 
	{
		if (::WaitForSingleObject (m_hThread, 0) == WAIT_TIMEOUT)
		{
			::TerminateThread (m_hThread, 5);
		
		}

		::CloseHandle(m_hThread);
	}

	if(m_hCloseThreadEvent)
		::CloseHandle(m_hCloseThreadEvent);
}

DWORD ThreadBase::threadProc ()
{
	DWORD	ret = 0;
	onInit();
	while(!isCloseEvent())
	{
		if(!onProcess())
		{
			ret = 2;
			break;
		}
	}
	onDestroy();
	return ret;
}

bool ThreadBase::createThread (bool bRun /*= true*/)
{
	if (!isCreated ()) 
	{
		// 创建关闭事件句柄
		m_hCloseThreadEvent = ::CreateEvent(NULL, false, false, NULL);		// "Close Thread"
		if(m_hCloseThreadEvent == NULL)
		{
		
			return false;
		}
		DWORD	dwThreadID;		// 不用，丢弃
		DWORD	dwCreationFlags = bRun ? 0 : CREATE_SUSPENDED;
		m_hThread = ::CreateThread (NULL, 0, (DWORD (WINAPI *)(LPVOID))trueThreadProc, 
			(void *)(ThreadBase *)this, dwCreationFlags, &dwThreadID);
		if(m_hThread)
		{
			return true;
		}
		else
		{
			::CloseHandle(m_hCloseThreadEvent);
			
			return false;
		}
	}
	else
	{
		
		return false;
	}
}

bool ThreadBase::resumeThread()	// return false: 失败
{
	if(m_hThread) 
	{
		if(::ResumeThread(m_hThread) != -1)
			return true;
	}
	else
	{
		int err = GetLastError();
	
	}

	return false;
}

bool ThreadBase::suspendThread()
{
	if(m_hThread) 
	{
		if(::SuspendThread(m_hThread) != -1)
			return true;
	}
	else
	{
		int err = GetLastError();

	}

	return false;
}

bool ThreadBase::closeThread(long nMilliseconds /*= 0*/)
{
	if(m_hThread)
	{    
		::ResumeThread(m_hThread);			// 冗余
		::SetEvent(m_hCloseThreadEvent);
		if(::WaitForSingleObject(m_hThread, nMilliseconds) != WAIT_TIMEOUT)		// 调用失败时也关闭。
		{   
			onDestroy();  //释放资源
			::CloseHandle(m_hThread);
			m_hThread = NULL;
			::CloseHandle(m_hCloseThreadEvent);
			m_hCloseThreadEvent = NULL;
		}
		else
		{
			return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
bool ThreadBase::isCloseEvent(long nMilliseconds /*= 0*/)			// 检查关闭线程事件是否触发。用于 ThreadProc() 函数调用
{
	if(::WaitForSingleObject(m_hCloseThreadEvent, nMilliseconds) != WAIT_TIMEOUT)
		return true;
	else
		return false;
}


//*********************************************************
//creates the thread
//*********************************************************
DWORD WINAPI ThreadBase::trueThreadProc(LPVOID pParam)
{
	ThreadBase *	pThread;
	pThread			= (ThreadBase*)pParam;
	return pThread->threadProc();
}





