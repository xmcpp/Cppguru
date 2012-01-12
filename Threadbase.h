#ifndef __THREADBASE_H__
#define __THREADBASE_H__

#include <windows.h>

class ThreadBase
{
public:		
	/// Ĭ�Ϲ��캯��
	ThreadBase();
	/// Ĭ����������
	virtual ~ThreadBase();

public:		
	// false: �ݲ����У��� ResumeThread() ����
	bool createThread(bool bRun = true);	

	// return false: ʧ��
	bool resumeThread();			

	// ֪ͨ���̹߳رգ������� nMilliseconds ���롣����true: �̹߳رճɹ�
	bool closeThread(long nMilliseconds = 0);
    
	bool suspendThread();
	
// ������
protected:	
	virtual	void	onInit() { }
	virtual bool	onProcess() { return true;};		
	virtual void	onDestroy() { }

// �ڲ�ʹ��
private:	
	// ���ر��߳��¼��Ƿ񴥷������� ThreadProc() ��������
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
