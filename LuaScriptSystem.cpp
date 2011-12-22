#include "pch.h"
#include "LuaScriptSystem.h"
#include "StringTools.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

};

LuaScriptSystem::LuaScriptSystem()
:m_state(NULL),m_bReplaced(false)
{
	
}

LuaScriptSystem::~LuaScriptSystem()
{
	
}

bool LuaScriptSystem::onInit()
{
	m_state = lua_open();
	return true;
}

bool LuaScriptSystem::onClear()
{
	if ( !m_bReplaced )
		lua_close( m_state );
	
	return true;
}

int LuaScriptSystem::getLuaStateTop()
{ 
	return lua_gettop( m_state ); 
}

bool LuaScriptSystem::executeFunction( const std::string & name )
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

bool LuaScriptSystem::executeFunction( const std::string & name , bool & ret )
{
	ret = false;

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
		return executeGlobalFunction( name , ret );
	}

	//表示有多于2个名称，调用到表中的函数
	int top = lua_gettop( m_state );

	if( !processTable( nameVec , top ) ) return false;

	//调用,无入参，无出参
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

bool LuaScriptSystem::executeGlobalFunction( const std::string & name )
{
	if ( !m_bEnable ) return false;

	int top = lua_gettop( m_state );

	if (!checkFunction( name ) ) return false;

	//调用,无入参，无出参
	lua_call( m_state , 0 , 0 );

	lua_settop( m_state , top );
	return true;
}

bool LuaScriptSystem::executeGlobalFunction( const std::string & name , bool & ret )
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

bool LuaScriptSystem::executeFile( const std::string & fileName )
{
	if ( !m_bEnable ) return false;

	int top = lua_gettop( m_state );

	//加载脚本文件
	if( luaL_loadfile( m_state , fileName.c_str() ) )
	{
		return false;
	}

	//调用,无入参，无出参
	if( lua_pcall( m_state , 0 , 0 , 0 ) )
	{
		//可以进行错误信息获取
		// std::string error = lua_tostring(m_state,-1);
		
	}


	lua_settop( m_state , top );
	return true;
}

bool LuaScriptSystem::checkFunction( const std::string & name )
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

bool LuaScriptSystem::processTable( std::vector<std::string> & stringVec , int top )
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

void LuaScriptSystem::replaceLuaState( lua_State * newState )
{
	if (m_bEnable && m_state )
	{
		onClear();
	}
	m_state = newState;
	m_bReplaced = true;
}