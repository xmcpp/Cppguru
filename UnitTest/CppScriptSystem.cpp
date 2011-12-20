#include "pch.h"
#include "CppScriptSystem.h"
#include "lua_ScriptSystem.h"

bool CppScriptSystem::onInit()
{
	LuaScriptSystem::onInit();
	luaopen_ScriptSystem( m_state );
	return true;
}

bool CppScriptSystem::onClear()
{
	LuaScriptSystem::onClear();
	return true;
}