#include "pch.h"
#include "TimerTestSuite.h"
#include "MessageDispatcher.h"

void TimerTestFixture::SetUpTestCase()
{
	new MessageDispatcher();
	new TimerManager();
}

void TimerTestFixture::TearDownTestCase()
{
	delete TimerManager::getSingletonPtr();
	delete MessageDispatcher::getSingletonPtr();
}

void TimerTestFixture::SetUp()
{
	
}

void TimerTestFixture::TearDown()
{
	TimerManager::getSingleton().destroyAllTimer();
}