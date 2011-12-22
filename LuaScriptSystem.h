/**********************************************************************
Lua脚本系统

Desc:
	本类根据脚本系统的接口，实现了一套可以操作lua脚本运行时的对象

Author: 徐淼

Date: 2011.12.20

Update: 
	2011.12.22
	增加了获得内部lua对象的方法。
	增加了替代内部lua对象的方法。
***********************************************************************/

#ifndef __LUASCRIPTSYSTEM_H__
#define __LUASCRIPTSYSTEM_H__

#include "ScriptSystem.h"
struct lua_State;
class LuaScriptSystem : public ScriptSystem
{
public:
	LuaScriptSystem();
	virtual ~LuaScriptSystem();
public:
	virtual bool onInit();
	virtual bool onClear();

	/**执行lua脚本中的全局函数
	@desc 该方法只能调用无输入和输出参数的全局lua函数
	*/
	bool executeGlobalFunction( const std::string & name );
	
	/**执行lua脚本中的全局函数
	@desc 该方法调用全局lua函数,并返回bool类型
	*/
	bool executeGlobalFunction( const std::string & name , bool & ret );
	
	/**执行lua脚本中函数,并不一定要求是全局函数
	@desc 该方法只能调用无输入和输出参数的lua函数,并且可以调用table中的方法，能自适应输入的名称中
	有 . 的方法，在调用时自动支持table的寻址方式
	*/
	bool executeFunction( const std::string & name );
	
	bool executeFunction( const std::string & name , bool & ret );

	/**加载lua文件并执行
	*/
	bool executeFile( const std::string & fileName );

public:
	//这方法帮助单元测试模块，用来监测各种调用之后是否有栈泄露
	int getLuaStateTop();

	/**获得内部的lua 对象*/
	lua_State * getLuaState(){ return m_state; }

	/**替换内部的lua 对象
	@desc 该方法可以将其它系统已经创建好的环境并进这个类来使用。
	需要注意的是一旦调用本方法，原有的对象会被关闭。同时本类析构
	的时候不会释放外部的lua对象
	*/
	void replaceLuaState( lua_State * newState );
protected:
	/**用于检查给定的名称是否是有效的全局函数*/
	bool checkFunction( const std::string & name );

	/**用于处理表中的函数展开，并将最后的函数置于栈顶
	@param stringVec 被拆分的表名和函数名，层数不限
	@param top 栈顶索引，用于处理给定名称无效时弹出栈内无效数据
	*/
	bool processTable( std::vector<std::string> & stringVec , int top );

protected:
	lua_State * m_state;
	bool m_bReplaced;
};


#endif //__LUASCRIPTSYSTEM_H__
