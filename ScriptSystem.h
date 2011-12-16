/**********************************************************************
脚本系统

Desc:
	本对象包装lua库的使用方法,提供简单的启动和调用lua脚本中函数的功能.
	实际使用时需要重载本类，可以在onInit事件中绑定自定义的函数。

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
	bool init();
	bool clear();
	
public:
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
	
	/**加载lua文件并执行
	*/
	bool executeFile( const std::string & fileName );
		
public:
	//这方法帮助单元测试模块，用来监测各种调用之后是否有栈泄露
	int getLuaStateTop();
protected:
	virtual bool onInit(){ return true; }
	virtual bool onClear(){ return true; }

	/**用于检查给定的名称是否是有效的全局函数*/
	bool checkFunction( const std::string & name );
	/**用于处理表中的函数展开，并将最后的函数置于栈顶
	@param stringVec 被拆分的表名和函数名，层数不限
	@param top 栈顶索引，用于处理给定名称无效时弹出栈内无效数据
	*/
	bool processTable( std::vector<std::string> & stringVec , int top );
protected:
	lua_State * m_state;
	bool m_bEnable; //记录当前是否是初始化后的状态，如果为false则所有函数不运行。
};

#endif //__SCRIPTSYSTEM_H__
