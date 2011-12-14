#include "pch.h"
#include "ScriptMonitorObject.h"
#include "ScriptSystem.h"

bool ScriptMonitorObject::onCheck()
{
	bool ret = false;
	if( !ScriptSystem::getSingleton().executeGlobalFunction( m_funName , ret ) )
		return false;

	return ret;
}