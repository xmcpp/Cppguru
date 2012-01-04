#ifndef __INIFILEMANAGERTESTSUITE_H__
#define __INIFILEMANAGERTESTSUITE_H__

#include "IniFileManager.h"

TEST( IniFileManagerTestSuite , ReadFileTest )
{
	IniFileManager mgr;
	ASSERT_TRUE( mgr.openIniFile( "IniTest.ini" ) );

	
}

#endif //__INIFILEMANAGERTESTSUITE_H__
