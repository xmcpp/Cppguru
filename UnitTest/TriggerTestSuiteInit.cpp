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
	m_objectSet = new ANDMonitorObject();
}

void TriggerTestSuiteInit::TearDown()
{
	delete m_objectSet;
	delete m_objectC;
	delete m_objectB;
	delete m_objectA;

}