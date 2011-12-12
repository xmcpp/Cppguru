#include "pch.h"
#include "TriggerTestSuiteInit.h"

void TriggerTestSuiteInit::SetUpTestCase()
{
	new MessageDispatcher();
}

void TriggerTestSuiteInit::TearDownTestCase()
{
	delete MessageDispatcher::getSingletonPtr();
}

void TriggerTestSuiteInit::SetUp()
{
	m_objectA = new IMonitorObject();
	m_objectB = new IMonitorObject();
	m_objectC = new IMonitorObject();

	m_objectA->init();
	m_objectB->init();
	m_objectC->init();
}

void TriggerTestSuiteInit::TearDown()
{
	m_objectC->clear();
	m_objectB->clear();
	m_objectA->clear();

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

void EventMonitorTest::SetUp()
{
	TriggerTestSuiteInit::SetUp();

	m_eventObj = new EventMonitorObject();
	m_eventObj->init();
	
}

void EventMonitorTest::TearDown()
{
	TriggerTestSuiteInit::TearDown();

	m_eventObj->clear();
	delete m_eventObj;
}

void PollMonitorTest::SetUp()
{
	TriggerTestSuiteInit::SetUp();

	m_pollObj = new TestPollMonitorObject();
	m_pollObj->init();

}

void PollMonitorTest::TearDown()
{
	TriggerTestSuiteInit::TearDown();

	m_pollObj->clear();
	delete m_pollObj;
}