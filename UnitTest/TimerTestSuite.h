#ifndef __TIMERTESTSUITE_H__
#define __TIMERTESTSUITE_H__

#include "TimerManager.h"
#include "TimerHelper.h"

class TimerTestFixture : public testing::Test
{
public:
	static void SetUpTestCase();
	static void TearDownTestCase();

	virtual void SetUp();
	virtual void TearDown();
};

TEST_F(TimerTestFixture , Create)
{
	ITimer * timer = TimerManager::getSingleton().createSequenceTimer( "a" );
	EXPECT_TRUE(  timer!= NULL );
	EXPECT_TRUE( TimerManager::getSingleton().createSequenceTimer( "a" ) == NULL );
	TimerManager::getSingleton().destroyTimer(timer);
	EXPECT_TRUE( TimerManager::getSingleton().createSequenceTimer( "a" ) != NULL );
	
	TimerManager::getSingleton().destroyAllTimer();
	EXPECT_TRUE( TimerManager::getSingleton().createSequenceTimer( "a" ) != NULL );
	EXPECT_TRUE( TimerManager::getSingleton().createCountDownTimer( "a" ) == NULL );
}

TEST_F( TimerTestFixture , SequenceTimerBaseTest )
{
	SequenceTimer * timer = TimerManager::getSingleton().createSequenceTimer( "a" );
	ASSERT_TRUE(  timer!= NULL );
	TimerHelper help;
	
	//��������״̬�л�����
	timer->addListener(&help);
	timer->start();
	EXPECT_TRUE( help.m_hasStartEvent );
	timer->pause();
	EXPECT_TRUE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_TRUE( help.m_hasResumeEvent );
	timer->stop();
	EXPECT_TRUE( help.m_hasStopEvent );
	
	//���Է�����״̬�л�
	help.reset();
	timer->pause();
	EXPECT_FALSE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_FALSE( help.m_hasResumeEvent );
	timer->stop();
	EXPECT_FALSE( help.m_hasStopEvent );
	
	timer->start();
	timer->resume();
	EXPECT_FALSE( help.m_hasResumeEvent );
	timer->pause();
	EXPECT_TRUE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_TRUE( help.m_hasResumeEvent );
	help.reset();
	
	timer->start();
	timer->pause();
	timer->stop();
	EXPECT_TRUE( help.m_hasStopEvent );

	timer->removeListener(&help);
}

TEST_F( TimerTestFixture , CountDownTimerBaseTest )
{
	CountDownTimer * timer = TimerManager::getSingleton().createCountDownTimer( "a" );
	ASSERT_TRUE(  timer!= NULL );
	TimerHelper help;
	timer->setCountDownTime( 3000 );

	//��������״̬�л�����
	timer->addListener(&help);
	timer->start();
	EXPECT_TRUE( help.m_hasStartEvent );
	timer->pause();
	EXPECT_TRUE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_TRUE( help.m_hasResumeEvent );
	timer->stop();
	EXPECT_TRUE( help.m_hasStopEvent );

	//���Է�����״̬�л�
	help.reset();
	timer->pause();
	EXPECT_FALSE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_FALSE( help.m_hasResumeEvent );
	timer->stop();
	EXPECT_FALSE( help.m_hasStopEvent );

	timer->start();
	timer->resume();
	EXPECT_FALSE( help.m_hasResumeEvent );
	timer->pause();
	EXPECT_TRUE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_TRUE( help.m_hasResumeEvent );
	help.reset();

	timer->start();
	timer->pause();
	timer->stop();
	EXPECT_TRUE( help.m_hasStopEvent );

	timer->removeListener(&help);
}

TEST_F( TimerTestFixture , SequenceTimerTest )
{
	SequenceTimer * timer = TimerManager::getSingleton().createSequenceTimer( "a" );
	ASSERT_TRUE(  timer!= NULL );
	TimerHelper help;
	timer->addListener(&help);
	timer->start();

	ParameterSet param;
	ITimer::FormatTimeStruct data;

	param.SetValue("interval","0.6"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.6����¼�
	timer->getFormatTime(data);
	EXPECT_EQ( 0 , data.m_seconds );
	EXPECT_EQ( 600 , data.m_milliSeconds );
	EXPECT_FALSE( help.m_hasSecondEvent );
	
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.6����¼�
	timer->getFormatTime(data);
	EXPECT_EQ( 1 , data.m_seconds );
	EXPECT_EQ( 200 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	help.m_hasSecondEvent = false;
	
	param.SetValue("interval","0.8"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.8����¼�
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	
	//������ͣ����
	timer->pause();
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//���;���0.8����¼�
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	
	//����ֹͣ�Ժ��ܷ�������
	timer->stop();
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	
	//���Կ�ʼʱ�Ƿ��������
	timer->start();
	timer->getFormatTime(data);
	EXPECT_EQ( 0 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );

	timer->removeListener(&help);
}

#endif //__TIMERTESTSUITE_H__
