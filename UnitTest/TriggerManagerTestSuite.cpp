#include "pch.h"
#include "TriggerManagerTestSuite.h"
#include "TriggerManager.h"
#include "MonitorObject.h"
#include "TestActionObject.h"
#include "MessageDispatcher.h"

void TriggerManagerTestSuite::SetUpTestCase()
{
	new MessageDispatcher();
	new TriggerManager();
	TriggerManager::getSingleton().initTriggerSystem();
}

void TriggerManagerTestSuite::TearDownTestCase()
{
	TriggerManager::getSingleton().uninitTriggerSystem();
	delete TriggerManager::getSingletonPtr();
	delete MessageDispatcher::getSingletonPtr();
}

void TriggerManagerTestSuite::SetUp()
{
	TriggerManager::getSingleton().getMonitorObjectManager()->addMonitorObject( new IMonitorObject("MonitorObject"));
	TriggerManager::getSingleton().getActionObjectManager()->addActionObject( new TestActionObject("ActionObject"));
}

void TriggerManagerTestSuite::TearDown()
{
	TriggerManager::getSingleton().getMonitorObjectManager()->removeMonitorObject( "MonitorObject" , true );
	TriggerManager::getSingleton().getActionObjectManager()->removeActionObject( "ActionObject" , true );
}