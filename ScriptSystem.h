/**********************************************************************
脚本系统

Desc:
	本类定义了脚本系统的通用方法，用户需要根据各种类型脚本进行重载。
	实际使用时需要重载本类，可以在onInit事件中绑定自定义的函数。

Author: 徐淼

Date: 2011.12.14

Update: 
2011.12.20
将本类修改为抽象基类

***********************************************************************/
#ifndef __SCRIPTSYSTEM_H__
#define __SCRIPTSYSTEM_H__

#include "Singleton.h"

class ScriptSystem
{
public:
	ScriptSystem();
	~ScriptSystem();
public:
	bool init();
	bool clear();
	
public:
	/**初始化和清理脚本环境回调函数，需要子类自行实现
	*/
	virtual bool onInit(){ return true; }
	virtual bool onClear(){ return true; }
	
	/**执行脚本中的全局函数
	@desc 该方法只能调用无输入和输出参数的全局函数
	*/
	virtual bool executeGlobalFunction( const std::string & name ){return true;}
	
	/**执行脚本中的全局函数
	@desc 该方法调用全局函数,并返回bool类型
	*/
	virtual bool executeGlobalFunction( const std::string & name , bool & ret ){return true;}
	
	/**执行脚本中函数,并不一定要求是全局函数
	*/
	virtual bool executeFunction( const std::string & name ){return true;}

	/**执行脚本中函数,并返回bool类型
	*/
	virtual bool executeFunction( const std::string & name , bool & ret ){return true;}
	
	/**加载文件并执行
	*/
	virtual bool executeFile( const std::string & fileName ){return true;}
protected:
	bool m_bEnable; //记录当前是否是初始化后的状态，如果为false则所有函数不运行。
};

class ScriptSystemManager : public Singleton<ScriptSystemManager>
{
public:
	ScriptSystemManager()
		:m_scriptSystem(NULL)
	{}
	~ScriptSystemManager(){}

public:
	ScriptSystem * getScriptSystem(){ return m_scriptSystem; }
	void setScriptSystem( ScriptSystem * system ){ m_scriptSystem = system;}
private:
	ScriptSystem * m_scriptSystem;
};


#endif //__SCRIPTSYSTEM_H__
