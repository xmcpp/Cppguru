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

TEST_F(TriggerTestSuiteInit , DeferredMonitorTest )
{
	//开启延迟启动，时间1秒
	m_objectA->enable( true , true );
	
	//此时应该未启动
	EXPECT_FALSE( m_objectA->isEnable() );
	ParameterSet param;
	param.SetValue("interval","0.3"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.3秒的事件
	EXPECT_FALSE( m_objectA->isEnable() );
	
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.3秒的事件
	EXPECT_FALSE( m_objectA->isEnable() );

	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.3秒的事件
	EXPECT_FALSE( m_objectA->isEnable() );

	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.3秒的事件
	//此时应该启动
	EXPECT_TRUE( m_objectA->isEnable() );
	
	//应该立即关闭
	m_objectA->enable( false );
	EXPECT_FALSE( m_objectA->isEnable() );

	//开启延迟启动，时间1秒
	m_objectA->enable( true , true );
	EXPECT_FALSE( m_objectA->isEnable() );

	param.SetValue("interval","0.6"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.6秒的事件
	EXPECT_FALSE( m_objectA->isEnable() );
	
	//中止延迟启动
	m_objectA->stopDeferredState();
	
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.6秒的事件
	EXPECT_FALSE( m_objectA->isEnable() ); //应该不会启动了
}


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
