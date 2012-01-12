#ifndef __THREADTESTSUITE_H__
#define __THREADTESTSUITE_H__

#include "TestThread.h"
#include "Windows.h"

TEST( ThreadTest , Test1 )
{
	TestThread * threadObj = new TestThread();
	threadObj->beginThread();
	Sleep(100);
	threadObj->endThread();
	EXPECT_EQ( 100 , threadObj->getValue() );

	threadObj->beginThread();
	Sleep(100);
	threadObj->endThread();
	EXPECT_EQ( 100 , threadObj->getValue() );
};

#endif // __THREADTESTSUITE_H__
