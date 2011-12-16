/**********************************************************************
�ű�ϵͳ

Desc:
	�������װlua���ʹ�÷���,�ṩ�򵥵������͵���lua�ű��к����Ĺ���.
	ʵ��ʹ��ʱ��Ҫ���ر��࣬������onInit�¼��а��Զ���ĺ�����

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
	bool init();
	bool clear();
	
public:
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
	
	/**����lua�ļ���ִ��
	*/
	bool executeFile( const std::string & fileName );
		
public:
	//�ⷽ��������Ԫ����ģ�飬���������ֵ���֮���Ƿ���ջй¶
	int getLuaStateTop();
protected:
	virtual bool onInit(){ return true; }
	virtual bool onClear(){ return true; }

	/**���ڼ������������Ƿ�����Ч��ȫ�ֺ���*/
	bool checkFunction( const std::string & name );
	/**���ڴ�����еĺ���չ�����������ĺ�������ջ��
	@param stringVec ����ֵı����ͺ���������������
	@param top ջ�����������ڴ������������Чʱ����ջ����Ч����
	*/
	bool processTable( std::vector<std::string> & stringVec , int top );
protected:
	lua_State * m_state;
	bool m_bEnable; //��¼��ǰ�Ƿ��ǳ�ʼ�����״̬�����Ϊfalse�����к��������С�
};

#endif //__SCRIPTSYSTEM_H__
