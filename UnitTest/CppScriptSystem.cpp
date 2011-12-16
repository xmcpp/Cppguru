#include "pch.h"
#include "CppScriptSystem.h"
#include "lua_ScriptSystem.h"

bool CppScriptSystem::onInit()
{
	luaopen_ScriptSystem( m_state );
	return true;
}

bool CppScriptSystem::onClear()
{
	return true;
}