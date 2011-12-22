/**********************************************************************
Lua�ű�ϵͳ

Desc:
	������ݽű�ϵͳ�Ľӿڣ�ʵ����һ�׿��Բ���lua�ű�����ʱ�Ķ���

Author: ���

Date: 2011.12.20

Update: 
	2011.12.22
	�����˻���ڲ�lua����ķ�����
	����������ڲ�lua����ķ�����
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

	/**ִ��lua�ű��е�ȫ�ֺ���
	@desc �÷���ֻ�ܵ�������������������ȫ��lua����
	*/
	bool executeGlobalFunction( const std::string & name );
	
	/**ִ��lua�ű��е�ȫ�ֺ���
	@desc �÷�������ȫ��lua����,������bool����
	*/
	bool executeGlobalFunction( const std::string & name , bool & ret );
	
	/**ִ��lua�ű��к���,����һ��Ҫ����ȫ�ֺ���
	@desc �÷���ֻ�ܵ�������������������lua����,���ҿ��Ե���table�еķ�����������Ӧ�����������
	�� . �ķ������ڵ���ʱ�Զ�֧��table��Ѱַ��ʽ
	*/
	bool executeFunction( const std::string & name );
	
	bool executeFunction( const std::string & name , bool & ret );

	/**����lua�ļ���ִ��
	*/
	bool executeFile( const std::string & fileName );

public:
	//�ⷽ��������Ԫ����ģ�飬���������ֵ���֮���Ƿ���ջй¶
	int getLuaStateTop();

	/**����ڲ���lua ����*/
	lua_State * getLuaState(){ return m_state; }

	/**�滻�ڲ���lua ����
	@desc �÷������Խ�����ϵͳ�Ѿ������õĻ��������������ʹ�á�
	��Ҫע�����һ�����ñ�������ԭ�еĶ���ᱻ�رա�ͬʱ��������
	��ʱ�򲻻��ͷ��ⲿ��lua����
	*/
	void replaceLuaState( lua_State * newState );
protected:
	/**���ڼ������������Ƿ�����Ч��ȫ�ֺ���*/
	bool checkFunction( const std::string & name );

	/**���ڴ�����еĺ���չ�����������ĺ�������ջ��
	@param stringVec ����ֵı����ͺ���������������
	@param top ջ�����������ڴ������������Чʱ����ջ����Ч����
	*/
	bool processTable( std::vector<std::string> & stringVec , int top );

protected:
	lua_State * m_state;
	bool m_bReplaced;
};


#endif //__LUASCRIPTSYSTEM_H__
