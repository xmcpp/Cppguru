#include "pch.h"
#include "ScriptMonitorObject.h"
#include "ScriptSystem.h"

bool ScriptMonitorObject::onCheck()
{
	bool result = false;
	ScriptSystem * sys = ScriptSystemManager::getSingleton().getScriptSystem();

	if( !sys ) return false;

	if( !sys->executeFunction( m_funName , result ) ) return false;

	return result;
}