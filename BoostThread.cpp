#include "pch.h"
#include "BoostThread.h"


BoostThread::BoostThread()
:m_thread(NULL),m_isRunning(false)
{
	
}

BoostThread::~BoostThread()
{


}

bool BoostThread::beginThread()
{
	if( m_thread ) return false;

	m_thread = new boost::thread( boost::bind(&BoostThread::threadProc,this) );
	return true;
}

bool BoostThread::endThread()
{
	if( !m_thread) return true;
	
	

	return true;
}

void BoostThread::threadProc()
{

}
