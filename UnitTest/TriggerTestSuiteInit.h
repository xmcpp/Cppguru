#ifndef __TRIGGERTESTSUITEINIT_H__
#define __TRIGGERTESTSUITEINIT_H__

#include "pch.h"
#include "PollMonitorManager.h"
#include "MessageDispatcher.h"
#include "MonitorObject.h"
#include "MonitorObjectSet.h"

class TriggerTestSuiteInit : public testing::Test
{
public:
	//这是静态方法，用在一组Test之间。
	static void SetUpTestCase();
	static void TearDownTestCase();

	virtual void SetUp();
	virtual void TearDown();


protected:
	IMonitorObject * m_objectA;
	IMonitorObject * m_objectB;
	IMonitorObject * m_objectC;
	ANDMonitorObject * m_objectSet;
};

TEST_F( TriggerTestSuiteInit , TestMonitorSet )
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


}

#endif //__TRIGGERTESTSUITEINIT_H__
