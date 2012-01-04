#ifndef __TRIGGERMANAGERTESTSUITE_H__
#define __TRIGGERMANAGERTESTSUITE_H__

#include "TriggerManager.h"
#include "TestActionObject.h"
class TriggerManagerTestSuite : public testing::Test
{
public:
	//这是静态方法，用在一组Tests之间。
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp();
	virtual void TearDown();
};

TEST_F( TriggerManagerTestSuite , TestTriggerFunction )
{
	TriggerObject * p = TriggerManager::getSingleton().createTrigger( "a" );
	EXPECT_TRUE( TriggerManager::getSingleton().getTrigger( "a" ) != NULL );
	EXPECT_TRUE( TriggerManager::getSingleton().getTrigger( "b" ) == NULL );

	EXPECT_TRUE( TriggerManager::getSingleton().destroyTrigger( "a" ) );
	EXPECT_FALSE( TriggerManager::getSingleton().destroyTrigger( "a" ) );

	EXPECT_TRUE( TriggerManager::getSingleton().getTrigger( "a" ) == NULL );
}

TEST_F( TriggerManagerTestSuite , TestTriggerFunction2 )
{
	TriggerObject * p = TriggerManager::getSingleton().createTrigger( "a" );
	ActionObjectManager * actMgr = TriggerManager::getSingleton().getActionObjectManager();
	ASSERT_TRUE( actMgr != NULL );
	MonitorObjectManager * monitorMgr = TriggerManager::getSingleton().getMonitorObjectManager();
	ASSERT_TRUE( monitorMgr != NULL );
	
	IActionObject * actionObj = actMgr->getActionObject( "ActionObject" );
	ASSERT_TRUE( actionObj != NULL );

	IMonitorObject * monitorObj = monitorMgr->getMonitorObject( "MonitorObject" );
	ASSERT_TRUE( monitorObj != NULL );
	
	p->setMonitorObject( monitorObj );
	p->setActiveActionObject( actionObj );
	monitorObj->enable( true );
	p->enable( true );
	
	monitorObj->trigger();

	TestActionObject * pTestActionObject = dynamic_cast<TestActionObject*>(actionObj);
	ASSERT_TRUE( pTestActionObject != NULL );
	
	EXPECT_TRUE( pTestActionObject->getTestState() );

}

#endif //__TRIGGERMANAGERTESTSUITE_H__
