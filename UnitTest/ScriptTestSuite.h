#ifndef __SCRIPTTESTSUITE_H__
#define __SCRIPTTESTSUITE_H__

#include "CppScriptSystem.h"
#include "MessageDispatcher.h"

class ScriptTestSuite : public testing::Test
{
public:
	//这是静态方法，用在一组Tests之间。
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp();
	virtual void TearDown();
protected:
	CppScriptSystem * m_scriptObj;
};

/**测试是否可以读取文件类型的脚本*/
TEST_F( ScriptTestSuite , ScriptLoadFileTest )
{
	int oldTop = m_scriptObj->getLuaStateTop(); //获得调用之前栈顶序号

	EXPECT_TRUE( m_scriptObj->executeFile( "test.lua" ) );
	
	int newTop = m_scriptObj->getLuaStateTop(); //获得调用之后栈顶序号
	EXPECT_TRUE( oldTop == newTop ); //如没有错误则应该相等，否则在某个分支上未恢复栈顶，出现泄露。
}

/**测试是否可以调用全局函数，调用返回1个bool类型的函数*/
TEST_F( ScriptTestSuite , ScriptCallFunctionWithBoolRet )
{
	int oldTop = m_scriptObj->getLuaStateTop();

	EXPECT_TRUE( m_scriptObj->executeFile( "test.lua" ) );
	EXPECT_TRUE( m_scriptObj->executeGlobalFunction( "setBoolValue" ) );
	bool ret = false;
	EXPECT_TRUE( m_scriptObj->executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	EXPECT_FALSE( m_scriptObj->executeGlobalFunction( "getIntValue" , ret ) );

	int newTop = m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**测试是否可以调用表中的函数*/
TEST_F( ScriptTestSuite , ScriptCallTableFunction )
{
	int oldTop =m_scriptObj->getLuaStateTop();

	EXPECT_TRUE(m_scriptObj->executeFile( "test.lua" ) );
	//调用表中的函数
	EXPECT_TRUE(m_scriptObj->executeFunction( "a.b" ) );
	
	//确实函数是否正确执行
	bool ret = false;
	EXPECT_TRUE(m_scriptObj->executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	int newTop =m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**测试是否可以调用表中的函数*/
TEST_F( ScriptTestSuite , ScriptCallNestTableFunction )
{
	int oldTop =m_scriptObj->getLuaStateTop();

	EXPECT_TRUE(m_scriptObj->executeFile( "test.lua" ) );
	//调用表中的函数
	EXPECT_TRUE(m_scriptObj->executeFunction( "z.b.f" ) );

	//确实函数是否正确执行
	bool ret = false;
	EXPECT_TRUE(m_scriptObj->executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	int newTop =m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**测试是否可以调用c++中的对象*/
TEST_F( ScriptTestSuite , CallCppObjectTest )
{
	int oldTop = m_scriptObj->getLuaStateTop();

	EXPECT_TRUE( m_scriptObj->executeFile( "cpptest.lua" ) );
	MessageDispatcher::getSingleton().Update(1.0f);
	//此时应该没有激活
	bool ret = false;
	m_scriptObj->executeGlobalFunction( "checkAlarm" , ret );
	EXPECT_FALSE( ret );

	//调用表中的函数,设置激活条件为true
	EXPECT_TRUE( m_scriptObj->executeFunction( "setValue" ) );
	MessageDispatcher::getSingleton().Update(1.0f);
	
	//此时应该激活了
	m_scriptObj->executeGlobalFunction( "checkAlarm" , ret );
	EXPECT_TRUE( ret );

	int newTop = m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

#endif //__SCRIPTTESTSUITE_H__
