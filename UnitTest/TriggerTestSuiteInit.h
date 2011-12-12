#ifndef __TRIGGERTESTSUITEINIT_H__
#define __TRIGGERTESTSUITEINIT_H__

#include "pch.h"
#include "MessageDispatcher.h"
#include "MonitorObject.h"
#include "MonitorObjectSet.h"
#include "EventMonitorObject.h"
#include "TestPollMonitorObject.h"

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

//延迟触发器测试
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


/**EventMonitor测试用例
*
*/
class EventMonitorTest : public TriggerTestSuiteInit
{
public:
	virtual void SetUp();
	virtual void TearDown();
protected:
	EventMonitorObject * m_eventObj;
};

TEST_F( EventMonitorTest , TestEventMonitor)
{
	m_eventObj->setMonitorEvent( 100 );
	m_eventObj->enable( true );

	EXPECT_FALSE(m_eventObj->isAlarmed());
	
	//发送其它事件，不能触发
	MessageDispatcher::getSingleton().SendMessage( 200 , ParameterSet::EmptyParameterSet );
	EXPECT_FALSE(m_eventObj->isAlarmed());
	
	//发送监听的时间，被触发
	MessageDispatcher::getSingleton().SendMessage( 100 , ParameterSet::EmptyParameterSet );
	EXPECT_TRUE(m_eventObj->isAlarmed());
}

/**PollMonitorObject测试用例
*
*/
class PollMonitorTest : public TriggerTestSuiteInit
{
public:
	virtual void SetUp();
	virtual void TearDown();
protected:
	TestPollMonitorObject * m_pollObj;
};

TEST_F( PollMonitorTest , TestPollMonitor)
{
	m_pollObj->enable( true );

	EXPECT_FALSE(m_pollObj->isAlarmed());
	
	ParameterSet param;
	param.SetValue("interval","0.05"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.05秒的事件
	EXPECT_FALSE(m_pollObj->isAlarmed());
	
	//检测失败，不触发
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.05秒的事件
	EXPECT_FALSE(m_pollObj->isAlarmed());

	m_pollObj->cheat();
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.05秒的事件
	EXPECT_FALSE(m_pollObj->isAlarmed());
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.05秒的事件

	//应该触发
	EXPECT_TRUE(m_pollObj->isAlarmed());

}

#endif //__TRIGGERTESTSUITEINIT_H__
