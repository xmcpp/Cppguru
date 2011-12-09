#ifndef __TRIGGERTESTSUITEINIT_H__
#define __TRIGGERTESTSUITEINIT_H__

#include "pch.h"
#include "PollMonitorManager.h"
#include "MessageDispatcher.h"
#include "MonitorObject.h"
#include "MonitorObjectSet.h"

/**触发器模块测试包
*
*/
class TriggerTestSuiteInit : public testing::Test
{
public:
	//这是静态方法，用在一组Tests之间。
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp();
	virtual void TearDown();
protected:
	IMonitorObject * m_objectA;
	IMonitorObject * m_objectB;
	IMonitorObject * m_objectC;
};

/**ANDMonitor测试用例
*
*/
class ANDMonitorTest : public TriggerTestSuiteInit
{
public:
	virtual void SetUp();
	virtual void TearDown();
protected:
	ANDMonitorObject * m_objectSet;
};

TEST_F( ANDMonitorTest , TestANDMonitorSet )
{
	m_objectSet->addMonitorObject( m_objectA );
	m_objectSet->addMonitorObject( m_objectB );
	m_objectSet->addMonitorObject( m_objectC );
	m_objectSet->enable( true );
	m_objectA->enable( true );
	m_objectB->enable( true );
	m_objectC->enable( true );

	m_objectA->trigger();
	m_objectB->trigger();
	
	EXPECT_FALSE(m_objectSet->isAlarmed());
	
	m_objectC->trigger();
	EXPECT_TRUE(m_objectSet->isAlarmed());
	
	m_objectB->unTrigger();
	EXPECT_FALSE(m_objectSet->isAlarmed());
}

/**ORMonitor测试用例
*
*/
class ORMonitorTest : public TriggerTestSuiteInit
{
public:
	virtual void SetUp();
	virtual void TearDown();
protected:
	ORMonitorObject * m_objectSet;
};

TEST_F( ORMonitorTest , TestORMonitorSet)
{
	m_objectSet->addMonitorObject( m_objectA );
	m_objectSet->addMonitorObject( m_objectB );
	m_objectSet->addMonitorObject( m_objectC );
	m_objectSet->enable( true );
	m_objectA->enable( true );
	m_objectB->enable( true );
	m_objectC->enable( true );

	EXPECT_FALSE(m_objectSet->isAlarmed());

	m_objectA->trigger();
	EXPECT_TRUE(m_objectSet->isAlarmed());
	
	m_objectB->trigger();
	EXPECT_TRUE(m_objectSet->isAlarmed());
	
	m_objectB->unTrigger();
	EXPECT_TRUE(m_objectSet->isAlarmed());
	
	m_objectA->unTrigger();
	EXPECT_FALSE(m_objectSet->isAlarmed());
}


#endif //__TRIGGERTESTSUITEINIT_H__
