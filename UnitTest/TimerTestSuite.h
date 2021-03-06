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
	
	//测试正常状态切换流程
	timer->addListener(&help);
	timer->start();
	EXPECT_TRUE( help.m_hasStartEvent );
	timer->pause();
	EXPECT_TRUE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_TRUE( help.m_hasResumeEvent );
	timer->stop();
	EXPECT_TRUE( help.m_hasStopEvent );
	
	//测试非正常状态切换
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

	//测试正常状态切换流程
	timer->addListener(&help);
	timer->start();
	EXPECT_TRUE( help.m_hasStartEvent );
	timer->pause();
	EXPECT_TRUE( help.m_hasPauseEvent );
	timer->resume();
	EXPECT_TRUE( help.m_hasResumeEvent );
	timer->stop();
	EXPECT_TRUE( help.m_hasStopEvent );

	//测试非正常状态切换
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
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.6秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 0 , data.m_seconds );
	EXPECT_EQ( 600 , data.m_milliSeconds );
	EXPECT_FALSE( help.m_hasSecondEvent );
	
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.6秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 1 , data.m_seconds );
	EXPECT_EQ( 200 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	help.m_hasSecondEvent = false;
	
	param.SetValue("interval","0.8"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.8秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	
	//测试暂停功能
	timer->pause();
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.8秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	
	//测试停止以后还能否获得数据
	timer->stop();
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	
	//测试开始时是否清空数据
	timer->start();
	timer->getFormatTime(data);
	EXPECT_EQ( 0 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );

	timer->removeListener(&help);
}

TEST_F( TimerTestFixture , CountDownTimerTest )
{
	CountDownTimer * timer = TimerManager::getSingleton().createCountDownTimer( "a" );
	ASSERT_TRUE(  timer!= NULL );
	timer->setCountDownTime( 3500 );
	TimerHelper help;
	timer->addListener(&help);
	timer->start();
	
	ParameterSet param;
	ITimer::FormatTimeStruct data;

	timer->getFormatTime(data);
	EXPECT_EQ( 3 , data.m_seconds );
	EXPECT_EQ( 500 , data.m_milliSeconds );
	
	//倒计时0.8秒
	param.SetValue("interval","0.8"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.8秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 700 , data.m_milliSeconds );
	EXPECT_FALSE( help.m_hasSecondEvent );
	
	//倒计时0.4秒，检测每秒事件是否发生
	param.SetValue("interval","0.4"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.4秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 2 , data.m_seconds );
	EXPECT_EQ( 300 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	help.m_hasSecondEvent = false;
	
	//倒计时0.8秒，检测第二次每秒事件是否发生
	param.SetValue("interval","0.8"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.8秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 1 , data.m_seconds );
	EXPECT_EQ( 500 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	help.reset();
	
	//测试暂停效果
	timer->pause();
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过0.8秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 1 , data.m_seconds );
	EXPECT_EQ( 500 , data.m_milliSeconds );
	
	//测试超过总时间的倒计时，检测是否停止
	timer->resume();

	param.SetValue("interval","1.6"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过1.6秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 0 , data.m_seconds );
	EXPECT_EQ( 0 , data.m_milliSeconds );
	EXPECT_TRUE( help.m_hasSecondEvent );
	EXPECT_TRUE( help.m_hasStopEvent );
	help.reset();

	//测试stop方法不会影响已有的数据
	timer->start();
	param.SetValue("interval","1.6"); 
	MessageDispatcher::getSingleton().SendMessage( MD_TIME_FRAMETICK , param );//发送经过1.6秒的事件
	timer->getFormatTime(data);
	EXPECT_EQ( 1 , data.m_seconds );
	EXPECT_EQ( 900 , data.m_milliSeconds );
	timer->stop();
	timer->getFormatTime(data);
	EXPECT_EQ( 1 , data.m_seconds );
	EXPECT_EQ( 900 , data.m_milliSeconds );


	timer->removeListener(&help);
}

#endif //__TIMERTESTSUITE_H__
