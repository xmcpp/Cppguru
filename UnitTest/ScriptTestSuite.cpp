#include "pch.h"
#include "ScriptTestSuite.h"


void ScriptTestSuite::SetUpTestCase()
{
	
}

void ScriptTestSuite::TearDownTestCase()
{

}

void ScriptTestSuite::SetUp()
{
	m_scriptObj = new CppScriptSystem();
	m_scriptObj->init();
}

void ScriptTestSuite::TearDown()
{
	m_scriptObj->clear();
	delete m_scriptObj;
}