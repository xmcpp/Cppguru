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

int ScriptSystem::getLuaStateTop()
{ 
	return lua_gettop( m_state ); 
}

bool ScriptSystem::executeGlobalFunction( const std::string & name )
{
	int top = lua_gettop( m_state );

	if (!checkFunction( name ) ) return false;

	//����,����Σ��޳���
	lua_call( m_state , 0 , 0 );
	
	lua_settop( m_state , top );
	return true;
}

bool ScriptSystem::executeGlobalFunction( const std::string & name , bool & ret )
{
	int top = lua_gettop( m_state );

	if (!checkFunction( name ) ) 
	{
		lua_settop( m_state , top );
		return false;
	}

	//����,����Σ�1������
	lua_call( m_state , 0 , 1 );
	
	//��鷵��ֵ�Ƿ���bool
	if ( !lua_isboolean( m_state , -1 ) )
	{
		lua_settop( m_state , top );
		return false;
	}
	
	//ת��Ϊbool
	ret = (lua_toboolean( m_state , -1 ) == 1)?true:false;

	lua_settop( m_state , top );

	return true;
}

bool ScriptSystem::executeFile( const std::string & fileName )
{
	int top = lua_gettop( m_state );
	
	//���ؽű��ļ�
	if( luaL_loadfile( m_state , fileName.c_str() ) )
	{
		return false;
	}
	
	//����,����Σ��޳���
	lua_call( m_state , 0 , 0 );
	
	lua_settop( m_state , top );
	return true;
}

bool ScriptSystem::checkFunction( const std::string & name )
{
	//���ָ�����Ƶĺ���
	lua_getglobal( m_state , name.c_str() );

	//����Ƿ��Ǻ�����-1��ʾջ��
	if( !lua_isfunction( m_state , -1 ) )
	{
		return false;
	}
	return true;
}