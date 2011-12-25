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

TEST_F( TimerTestFixture , SequenceTimerTest )
{
	SequenceTimer * timer = TimerManager::getSingleton().createSequenceTimer( "a" );
	EXPECT_TRUE(  timer!= NULL );
	TimerHelper help;

	timer->addListener(&help);
	timer->start();
	EXPECT_TRUE( help.m_hasStartEvent );

	timer->removeListener(&help);
}




#endif //__TIMERTESTSUITE_H__
