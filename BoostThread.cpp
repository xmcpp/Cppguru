#include "pch.h"
#include "BoostThread.h"


BoostThread::BoostThread()
:m_thread(NULL),m_bStop(false)
{
	
}

BoostThread::~BoostThread()
{


}

bool BoostThread::beginThread()
{
	if( m_thread ) return false;

	m_thread = new boost::thread( boost::bind(&BoostThread::threadProc,this) );
	m_bStop = false;
	return true;
}

bool BoostThread::endThread()
{
	if( !m_thread) return true;
	
	m_bStop = true;
	m_thread->join();

	delete m_thread;
	m_thread = NULL;

	return true;
}

void BoostThread::threadProc()
{
	onBegin();
	
	while(!m_bStop)
	{
		m_bStop = !onProcess();
	}

	onEnd();
}
