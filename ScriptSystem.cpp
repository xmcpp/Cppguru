#include "pch.h"
#include "ScriptSystem.h"
#include "StringTools.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

};

template<> ScriptSystem* Singleton<ScriptSystem>::ms_Singleton	= 0;

ScriptSystem::ScriptSystem()
:m_state(NULL),m_bEnable(false)
{
	m_state = lua_open();
}

ScriptSystem::~ScriptSystem()
{
	lua_close( m_state );
}

bool ScriptSystem::init()
{
	bool ret = onInit();
	if ( ret )
	{
		m_bEnable = true;
	}
	return ret;
}

bool ScriptSystem::clear()
{
	bool ret = onClear();
	m_bEnable = false;
	return ret;
}

int ScriptSystem::getLuaStateTop()
{ 
	return lua_gettop( m_state ); 
}

bool ScriptSystem::executeFunction( const std::string & name )
{
	if ( !m_bEnable ) return false;
	
	std::vector<std::string> nameVec;
	StringTools::splitString( name , nameVec , '.' );

	if ( nameVec.size() == 0 )
	{
		//表示无名称
		return false;
	}
	else if ( nameVec.size() == 1 )
	{
		//表示调用全局函数
		return executeGlobalFunction( name );
	}

	//表示有多于2个名称，调用到表中的函数
	int top = lua_gettop( m_state );
	
	if( !processTable( nameVec , top ) ) return false;
	
	//调用,无入参，无出参
	lua_call( m_state , 0 , 0 );

	lua_settop( m_state , top );
	return true;
}

bool ScriptSystem::executeGlobalFunction( const std::string & name )
{
	if ( !m_bEnable ) return false;

	int top = lua_gettop( m_state );
	
	if (!checkFunction( name ) ) return false;

	//调用,无入参，无出参
	lua_call( m_state , 0 , 0 );
	
	lua_settop( m_state , top );
	return true;
}

bool ScriptSystem::executeGlobalFunction( const std::string & name , bool & ret )
{
	if ( !m_bEnable ) return false;

	int top = lua_gettop( m_state );

	if (!checkFunction( name ) ) 
	{
		lua_settop( m_state , top );
		return false;
	}

	//调用,无入参，1个出参
	lua_call( m_state , 0 , 1 );
	
	//检查返回值是否是bool
	if ( !lua_isboolean( m_state , -1 ) )
	{
		lua_settop( m_state , top );
		return false;
	}
	
	//转换为bool
	ret = (lua_toboolean( m_state , -1 ) == 1)?true:false;

	lua_settop( m_state , top );

	return true;
}

bool ScriptSystem::executeFile( const std::string & fileName )
{
	if ( !m_bEnable ) return false;

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

bool ScriptSystem::checkFunction( const std::string & name )
{
	//获得指定名称的函数
	lua_getglobal( m_state , name.c_str() );

	//检测是否是函数，-1表示栈顶
	if( !lua_isfunction( m_state , -1 ) )
	{
		return false;
	}
	return true;
}

bool ScriptSystem::processTable( std::vector<std::string> & stringVec , int top )
{
	lua_getglobal( m_state , stringVec[0].c_str() );
	if( !lua_istable( m_state , -1 ) )
	{
		lua_pop(m_state,-1);
		return false;
	}

	int count = stringVec.size();
	for ( int i = 1 ; i < count - 1 ; i++ )
	{
		lua_getfield( m_state , -1 , stringVec[i].c_str() );	
		if( !lua_istable( m_state , -1 ) )
		{
			lua_settop( m_state , top );
			return false;
		}
		//弹出表对象
		lua_remove( m_state , -2 );
	}

	lua_getfield( m_state , -1 , stringVec[count-1].c_str() );	
	if( !lua_isfunction( m_state , -1 ) )
	{
		lua_settop( m_state , top );
		return false;
	}

	//弹出表对象
	lua_remove( m_state , -2 );

	return true;
}