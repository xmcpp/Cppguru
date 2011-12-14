#include "pch.h"
#include "ScriptTestSuite.h"


void ScriptTestSuite::SetUpTestCase()
{
	new ScriptSystem();
}

void ScriptTestSuite::TearDownTestCase()
{
	delete ScriptSystem::getSingletonPtr();
}