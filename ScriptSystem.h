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
	/**ִ��lua�ű��е�ȫ�ֺ���
	@desc �÷���ֻ�ܵ�������������������lua����
	����Ҫ�����ܵ�����table�еķ��������������Ӧ������������� . �ģ��ڵ���ʱ�Զ�֧��table��Ѱַ��ʽ
	*/
	bool executeGlobalFunction( const std::string & name );
	
	bool executeGlobalFunction( const std::string & name , bool & ret );

	bool executeFile( const std::string & fileName );

public:
	//�ⷽ��������Ԫ����ģ�飬���������ֵ���֮���Ƿ���ջй¶
	int getLuaStateTop();
private:
	bool checkFunction( const std::string & name );
private:
	lua_State * m_state;
};

#endif //__SCRIPTSYSTEM_H__
