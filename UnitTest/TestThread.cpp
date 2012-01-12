#include "pch.h"
#include "TestThread.h"

TestThread::TestThread()
{

}

TestThread::~TestThread()
{

}

void TestThread::onBegin()
{
	m_value = 0;
}

bool TestThread::onProcess()
{
	m_value++;

	if( m_value >= 100 )
		return false;

	return true;
}

void TestThread::onEnd()
{

}
