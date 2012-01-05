#ifndef __INIFILEMANAGERTESTSUITE_H__
#define __INIFILEMANAGERTESTSUITE_H__

#include "IniFileManager.h"

TEST( IniFileManagerTestSuite , ReadFileTest )
{
	IniFileManager mgr;
	ASSERT_TRUE( mgr.loadIniFile( "IniTest.ini" ) );
	
	std::vector<std::string> nameList;
	mgr.getSectionName( nameList );
	EXPECT_EQ( 3 , nameList.size() );
	EXPECT_EQ( "Engine" , nameList[0] );
	EXPECT_EQ( "Render" , nameList[1] );
	EXPECT_EQ( "Test" , nameList[2] );
	
	mgr.getKeyName( "Engine" , nameList );
	EXPECT_EQ( 1 , nameList.size() );
	EXPECT_EQ( "Version" , nameList[0] );

	mgr.getKeyName( "Render" , nameList );
	EXPECT_EQ( 3 , nameList.size() );
	
	mgr.getKeyName( "Test" , nameList );
	EXPECT_EQ( 0 , nameList.size() );

	EXPECT_TRUE( mgr.hasSectionName( "Engine" ) );
	EXPECT_TRUE( mgr.hasSectionName( "Render" ) );
	EXPECT_FALSE( mgr.hasSectionName( "zzz" ) );
	
	EXPECT_TRUE( mgr.hasKeyName( "Engine" , "Version" ) );
	EXPECT_FALSE( mgr.hasKeyName( "Engine" , "Name" ) );
	EXPECT_FALSE( mgr.hasKeyName( "ZZZ" , "Name" ) );
	
	EXPECT_EQ( "v1.0" , mgr.getValue( "Engine" , "Version" ) );
	EXPECT_EQ( "720" , mgr.getValue( "Render" , "Height" ) );

	EXPECT_EQ( "" , mgr.getValue( "Test" , "Power" ) );
	EXPECT_EQ( "" , mgr.getValue( "ZZZ" , "Life" ) );


}

#endif //__INIFILEMANAGERTESTSUITE_H__
