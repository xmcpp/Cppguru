#include "pch.h"
#include "ScriptSystem.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

};

template<> ScriptSystem* Singleton<ScriptSystem>::ms_Singleton	= 0;

ScriptSystem::ScriptSystem()
:m_state(NULL)
{
	m_state = lua_open();
}

ScriptSystem::~ScriptSystem()
{
	lua_close( m_state );
}

bool ScriptSystem::executeGlobalFunction( const std::string & name )
{
	int top = lua_gettop( m_state );

	//获得指定名称的函数
	lua_getglobal( m_state , name.c_str() );
	
	//检测是否是函数，-1表示栈顶
	if( !lua_isfunction( m_state , -1 ) )
	{
		return false;
	}

	//调用,无入参，无出参
	lua_call( m_state , 0 , 0 );
	
	lua_settop( m_state , top );
	return true;
}

bool ScriptSystem::executeFile( const std::string & fileName )
{
	int top = lua_gettop( m_state );
	
	//加载脚本文件
	if( luaL_loadfile( m_state , fileName.c_str() ) )
	{
		return false;
	}
	
	//调用,无入参，无出参
	lua_call( m_state , 0 , 0 );
	
	lua_settop( m_state , top );
	return true;
}
