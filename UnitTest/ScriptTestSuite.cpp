#include "pch.h"
#include "ScriptTestSuite.h"
#include "ScriptSystem.h"
#include "ScriptMonitorObject.h"

void ScriptTestSuite::SetUpTestCase()
{
	new MessageDispatcher();
	new ScriptSystemManager();
}

void ScriptTestSuite::TearDownTestCase()
{
	delete ScriptSystemManager::getSingletonPtr();
	delete MessageDispatcher::getSingletonPtr();
}

void ScriptTestSuite::SetUp()
{
	m_scriptObj = new CppScriptSystem();
	m_scriptObj->init();

	ScriptSystemManager::getSingleton().setScriptSystem( m_scriptObj );
}

void ScriptTestSuite::TearDown()
{
	ScriptSystemManager::getSingleton().setScriptSystem( NULL );
	m_scriptObj->clear();
	delete m_scriptObj;
}