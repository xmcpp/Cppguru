#ifndef __STRINGTESTSUITE_H__
#define __STRINGTESTSUITE_H__

#include "StringTools.h"

TEST(StringToolTest , SplitTest)
{
	std::vector<std::string> stringVec;

	StringTools::splitString( "a.b.c" , stringVec , '.' );

	ASSERT_EQ( 3 , stringVec.size() );
	EXPECT_EQ( "a" , stringVec[0] );
	EXPECT_EQ( "b" , stringVec[1] );
	EXPECT_EQ( "c" , stringVec[2] );
}

TEST(StringToolTest , SplitTest2)
{
	std::vector<std::string> stringVec;

	StringTools::splitString( "a" , stringVec , '.' );

	ASSERT_EQ( 1 , stringVec.size() );
	EXPECT_EQ( "a" , stringVec[0] );
}

TEST(StringToolTest , SplitTest3)
{
	std::vector<std::string> stringVec;

	StringTools::splitString( "" , stringVec , '.' );

	ASSERT_EQ( 0 , stringVec.size() );
}

TEST(StringToolTest , SplitTest4)
{
	std::vector<std::string> stringVec;

	StringTools::splitString( "a" , stringVec , 0 );

	ASSERT_EQ( 1 , stringVec.size() );
	EXPECT_EQ( "a" , stringVec[0] );
}
#endif //__STRINGTESTSUITE_H__
