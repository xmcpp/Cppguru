#ifndef __SCRIPTTESTSUITE_H__
#define __SCRIPTTESTSUITE_H__

#include "CppScriptSystem.h"
#include "MessageDispatcher.h"

class ScriptTestSuite : public testing::Test
{
public:
	//���Ǿ�̬����������һ��Tests֮�䡣
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp();
	virtual void TearDown();
protected:
	CppScriptSystem * m_scriptObj;
};

/**�����Ƿ���Զ�ȡ�ļ����͵Ľű�*/
TEST_F( ScriptTestSuite , ScriptLoadFileTest )
{
	int oldTop = m_scriptObj->getLuaStateTop(); //��õ���֮ǰջ�����

	EXPECT_TRUE( m_scriptObj->executeFile( "test.lua" ) );
	
	int newTop = m_scriptObj->getLuaStateTop(); //��õ���֮��ջ�����
	EXPECT_TRUE( oldTop == newTop ); //��û�д�����Ӧ����ȣ�������ĳ����֧��δ�ָ�ջ��������й¶��
}

/**�����Ƿ���Ե���ȫ�ֺ��������÷���1��bool���͵ĺ���*/
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

/**�����Ƿ���Ե��ñ��еĺ���*/
TEST_F( ScriptTestSuite , ScriptCallTableFunction )
{
	int oldTop =m_scriptObj->getLuaStateTop();

	EXPECT_TRUE(m_scriptObj->executeFile( "test.lua" ) );
	//���ñ��еĺ���
	EXPECT_TRUE(m_scriptObj->executeFunction( "a.b" ) );
	
	//ȷʵ�����Ƿ���ȷִ��
	bool ret = false;
	EXPECT_TRUE(m_scriptObj->executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	int newTop =m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**�����Ƿ���Ե��ñ��еĺ���*/
TEST_F( ScriptTestSuite , ScriptCallNestTableFunction )
{
	int oldTop =m_scriptObj->getLuaStateTop();

	EXPECT_TRUE(m_scriptObj->executeFile( "test.lua" ) );
	//���ñ��еĺ���
	EXPECT_TRUE(m_scriptObj->executeFunction( "z.b.f" ) );

	//ȷʵ�����Ƿ���ȷִ��
	bool ret = false;
	EXPECT_TRUE(m_scriptObj->executeGlobalFunction( "getBoolValue" , ret ) );
	EXPECT_TRUE( ret );

	int newTop =m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

/**�����Ƿ���Ե���c++�еĶ���*/
TEST_F( ScriptTestSuite , CallCppObjectTest )
{
	int oldTop = m_scriptObj->getLuaStateTop();

	EXPECT_TRUE( m_scriptObj->executeFile( "cpptest.lua" ) );
	MessageDispatcher::getSingleton().Update(1.0f);
	//��ʱӦ��û�м���
	bool ret = false;
	m_scriptObj->executeGlobalFunction( "checkAlarm" , ret );
	EXPECT_FALSE( ret );

	//���ñ��еĺ���,���ü�������Ϊtrue
	EXPECT_TRUE( m_scriptObj->executeFunction( "setValue" ) );
	MessageDispatcher::getSingleton().Update(1.0f);
	
	//��ʱӦ�ü�����
	m_scriptObj->executeGlobalFunction( "checkAlarm" , ret );
	EXPECT_TRUE( ret );

	int newTop = m_scriptObj->getLuaStateTop();
	EXPECT_TRUE( oldTop == newTop );
}

#endif //__SCRIPTTESTSUITE_H__
