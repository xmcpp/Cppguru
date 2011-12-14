/**********************************************************************
脚本系统

Desc:
	本对象包装lua库的使用方法,提供简单的启动和调用lua脚本中函数的功能.

Author: 徐淼

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
