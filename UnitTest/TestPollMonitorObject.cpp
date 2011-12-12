#include "pch.h"
#include "TestPollMonitorObject.h"

TestPollMonitorObject::TestPollMonitorObject()
:m_isTrue(false)
{

}

bool TestPollMonitorObject::onCheck()
{
	return m_isTrue;
}

void TestPollMonitorObject::cheat()
{
	m_isTrue = true;
}