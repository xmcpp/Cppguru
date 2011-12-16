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
		//��ʾ������
		return false;
	}
	else if ( nameVec.size() == 1 )
	{
		//��ʾ����ȫ�ֺ���
		return executeGlobalFunction( name );
	}

	//��ʾ�ж���2�����ƣ����õ����еĺ���
	int top = lua_gettop( m_state );
	
	if( !processTable( nameVec , top ) ) return false;
	
	//����,����Σ��޳���
	lua_call( m_state , 0 , 0 );

	lua_settop( m_state , top );
	return true;
}

bool ScriptSystem::executeGlobalFunction( const std::string & name )
{
	if ( !m_bEnable ) return false;

	int top = lua_gettop( m_state );
	
	if (!checkFunction( name ) ) return false;

	//����,����Σ��޳���
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
	if ( !m_bEnable ) return false;

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
		//���������
		lua_remove( m_state , -2 );
	}

	lua_getfield( m_state , -1 , stringVec[count-1].c_str() );	
	if( !lua_isfunction( m_state , -1 ) )
	{
		lua_settop( m_state , top );
		return false;
	}

	//���������
	lua_remove( m_state , -2 );

	return true;
}