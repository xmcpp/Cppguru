#ifndef __TRIGGERTESTSUITEINIT_H__
#define __TRIGGERTESTSUITEINIT_H__

#include "pch.h"
#include "MessageDispatcher.h"
#include "MonitorObject.h"
#include "MonitorObjectSet.h"
#include "EventMonitorObject.h"
#include "TestPollMonitorObject.h"

/**������ģ����԰�
*
*/
class TriggerTestSuiteInit : public testing::Test
{
public:
	//���Ǿ�̬����������һ��Tests֮�䡣
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp();
	virtual void TearDown();
protected:
	IMonitorObject * m_objectA;
	IMonitorObject * m_objectB;
	IMonitorObject * m_objectC;
};

//�ӳٴ���������
TEST_F(TriggerTestSuiteInit , DeferredMonitorTest )
{
	//�����ӳ�������ʱ��1��
	m_objectA->enable( true , true );
	
	//��ʱӦ��δ����
	EXPECT_FALSE( m_objectA->isEnable() );
	ParameterSet param;
	param.SetValue("interval","0.3"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.3����¼�
	EXPECT_FALSE( m_objectA->isEnable() );
	
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.3����¼�
	EXPECT_FALSE( m_objectA->isEnable() );

	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.3����¼�
	EXPECT_FALSE( m_objectA->isEnable() );

	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.3����¼�
	//��ʱӦ������
	EXPECT_TRUE( m_objectA->isEnable() );
	
	//Ӧ�������ر�
	m_objectA->enable( false );
	EXPECT_FALSE( m_objectA->isEnable() );

	//�����ӳ�������ʱ��1��
	m_objectA->enable( true , true );
	EXPECT_FALSE( m_objectA->isEnable() );

	param.SetValue("interval","0.6"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.6����¼�
	EXPECT_FALSE( m_objectA->isEnable() );
	
	//��ֹ�ӳ�����
	m_objectA->stopDeferredState();
	
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.6����¼�
	EXPECT_FALSE( m_objectA->isEnable() ); //Ӧ�ò���������
}

/**ANDMonitor��������
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

/**ORMonitor��������
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


/**EventMonitor��������
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
	
	//���������¼������ܴ���
	MessageDispatcher::getSingleton().SendMessage( 200 , ParameterSet::EmptyParameterSet );
	EXPECT_FALSE(m_eventObj->isAlarmed());
	
	//���ͼ�����ʱ�䣬������
	MessageDispatcher::getSingleton().SendMessage( 100 , ParameterSet::EmptyParameterSet );
	EXPECT_TRUE(m_eventObj->isAlarmed());
}

/**PollMonitorObject��������
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
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.05����¼�
	EXPECT_FALSE(m_pollObj->isAlarmed());
	
	//���ʧ�ܣ�������
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.05����¼�
	EXPECT_FALSE(m_pollObj->isAlarmed());

	m_pollObj->cheat();
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.05����¼�
	EXPECT_FALSE(m_pollObj->isAlarmed());
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.05����¼�

	//Ӧ�ô���
	EXPECT_TRUE(m_pollObj->isAlarmed());

}

#endif //__TRIGGERTESTSUITEINIT_H__
