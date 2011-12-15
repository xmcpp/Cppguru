#ifndef __SCRIPTTESTSUITE_H__
#define __SCRIPTTESTSUITE_H__

#include "ScriptSystem.h"

class ScriptTestSuite : public testing::Test
{
public:
	//���Ǿ�̬����������һ��Tests֮�䡣
	static void SetUpTestCase();
	static void TearDownTestCase();
};

/**�����Ƿ���Զ�ȡ�ļ����͵Ľű�*/
TEST_F( ScriptTestSuite , ScriptLoadFileTest )
{
	int oldTop = ScriptSystem::getSingleton().getLuaStateTop(); //��õ���֮ǰջ�����

	EXPECT_TRUE( ScriptSystem::getSingleton().executeFile( "test.lua" ) );
	
	int newTop = ScriptSystem::getSingleton().getLuaStateTop(); //��õ���֮��ջ�����
	EXPECT_TRUE( oldTop == newTop ); //��û�д�����Ӧ����ȣ�������ĳ����֧��δ�ָ�ջ��������й¶��
}

/**�����Ƿ���Ե���ȫ�ֺ��������÷���1��bool���͵ĺ���*/
TEST_F( ScriptTestSuite , ScriptCallFunctionWithBoolRet )
{
	int oldTop = ScriptSystem::getSingleton().getLuaStateTop();

	EXPECT_TRUE( ScriptSystem::getSingleton().executeFile( "test.lua" ) );
	EXPECT_TRUE( ScriptSystem::getSingleton().executeGlobalFunction( "setBoolValue" ) );
	bool ret = false;
	EXPECT_TRUE( ScriptSystem::getSingleton().executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	EXPECT_FALSE( ScriptSystem::getSingleton().executeGlobalFunction( "getIntValue" , ret ) );

	int newTop = ScriptSystem::getSingleton().getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**�����Ƿ���Ե��ñ��еĺ���*/
TEST_F( ScriptTestSuite , ScriptCallTableFunction )
{
	int oldTop = ScriptSystem::getSingleton().getLuaStateTop();

	EXPECT_TRUE( ScriptSystem::getSingleton().executeFile( "test.lua" ) );
	//���ñ��еĺ���
	EXPECT_TRUE( ScriptSystem::getSingleton().executeFunction( "a.b" ) );
	
	//ȷʵ�����Ƿ���ȷִ��
	bool ret = false;
	EXPECT_TRUE( ScriptSystem::getSingleton().executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	int newTop = ScriptSystem::getSingleton().getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**�����Ƿ���Ե��ñ��еĺ���*/
TEST_F( ScriptTestSuite , ScriptCallNestTableFunction )
{
	int oldTop = ScriptSystem::getSingleton().getLuaStateTop();

	EXPECT_TRUE( ScriptSystem::getSingleton().executeFile( "test.lua" ) );
	//���ñ��еĺ���
	EXPECT_TRUE( ScriptSystem::getSingleton().executeFunction( "z.b.f" ) );

	//ȷʵ�����Ƿ���ȷִ��
	bool ret = false;
	EXPECT_TRUE( ScriptSystem::getSingleton().executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	int newTop = ScriptSystem::getSingleton().getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}
#endif //__SCRIPTTESTSUITE_H__
