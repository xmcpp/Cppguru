#include "pch.h"
#include "ScriptSystem.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

};

ScriptSystem::ScriptSystem()
:m_state(NULL)
{
	m_state = lua_open();
}

ScriptSystem::~ScriptSystem()
{
	lua_close( m_state );
}

