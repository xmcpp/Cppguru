/**********************************************************************
�ű�ϵͳ

Desc:
	�������װlua���ʹ�÷���,�ṩ�򵥵������͵���lua�ű��к����Ĺ���.

Author: ���

Date: 2011.12.14

Update: 

***********************************************************************/
#ifndef __SCRIPTSYSTEM_H__
#define __SCRIPTSYSTEM_H__

#include "Singleton.h"
struct lua_State;

class ScriptSystem : public Singleton<ScriptSystem>
{
public:
	ScriptSystem();
	~ScriptSystem();
public:
	bool executeGlobalFunction( const std::string & name );

	bool executeFile( const std::string & fileName );
private:
	lua_State * m_state;
};

#endif //__SCRIPTSYSTEM_H__
