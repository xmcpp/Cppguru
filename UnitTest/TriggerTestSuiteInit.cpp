#include "stdafx.h"
#include "TriggerTestSuiteInit.h"

//


#include "PollMonitorManager.cpp"
#include "MessageDispatcher.cpp"
#include "StringConverter.cpp"
#include "ParameterSet.cpp"
#include "MonitorObject.cpp"
#include "MonitorObjectSet.cpp"

void TriggerTestSuiteInit::SetUpTestCase()
{
	new MessageDispatcher();
	new PollMonitorManager();
}

void TriggerTestSuiteInit::TearDownTestCase()
{
	delete PollMonitorManager::getSingletonPtr();
	delete MessageDispatcher::getSingletonPtr();
}

void TriggerTestSuiteInit::SetUp()
{
	m_objectA = new IMonitorObject();
	m_objectB = new IMonitorObject();
	m_objectC = new IMonitorObject();
}

void TriggerTestSuiteInit::TearDown()
{
	delete m_objectC;
	delete m_objectB;
	delete m_objectA;

}

void ANDMonitorTest::SetUp()
{
	TriggerTestSuiteInit::SetUp();

	m_objectSet = new ANDMonitorObject();
}

void ANDMonitorTest::TearDown()
{
	TriggerTestSuiteInit::TearDown();

	m_objectSet->clear();
	delete m_objectSet;
}

void ORMonitorTest::SetUp()
{
	TriggerTestSuiteInit::SetUp();

	m_objectSet = new ORMonitorObject();
}

void ORMonitorTest::TearDown()
{
	TriggerTestSuiteInit::TearDown();

	m_objectSet->clear();
	delete m_objectSet;
}