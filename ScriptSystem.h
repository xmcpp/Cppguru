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
	/**执行lua脚本中的全局函数
	@desc 该方法只能调用无输入和输出参数的lua函数
	还需要考虑能调用在table中的方法，最好能自适应输入的名称中有 . 的，在调用时自动支持table的寻址方式
	*/
	bool executeGlobalFunction( const std::string & name );
	
	bool executeGlobalFunction( const std::string & name , bool & ret );

	bool executeFile( const std::string & fileName );

public:
	//这方法帮助单元测试模块，用来监测各种调用之后是否有栈泄露
	int getLuaStateTop();
private:
	bool checkFunction( const std::string & name );
private:
	lua_State * m_state;
};

#endif //__SCRIPTSYSTEM_H__
