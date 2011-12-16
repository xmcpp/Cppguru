#include "pch.h"
#include "ScriptTestSuite.h"


void ScriptTestSuite::SetUpTestCase()
{
	new ScriptSystem();
	ScriptSystem::getSingleton().init();
}

void ScriptTestSuite::TearDownTestCase()
{
	ScriptSystem::getSingleton().clear();
	delete ScriptSystem::getSingletonPtr();
}