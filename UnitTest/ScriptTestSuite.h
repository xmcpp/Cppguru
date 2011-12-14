#ifndef __SCRIPTTESTSUITE_H__
#define __SCRIPTTESTSUITE_H__

#include "ScriptSystem.h"

class ScriptTestSuite : public testing::Test
{
public:
	//这是静态方法，用在一组Tests之间。
	static void SetUpTestCase();
	static void TearDownTestCase();
};


TEST_F( ScriptTestSuite , ScriptLoadFileTest )
{
	EXPECT_TRUE( ScriptSystem::getSingleton().executeFile( "test.lua" ) );
	EXPECT_TRUE( ScriptSystem::getSingleton().executeGlobalFunction( "cppgurutest" ) );
	
}

#endif //__SCRIPTTESTSUITE_H__
