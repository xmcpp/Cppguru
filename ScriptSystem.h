/**********************************************************************
�ű�ϵͳ

Desc:
	���ඨ���˽ű�ϵͳ��ͨ�÷������û���Ҫ���ݸ������ͽű��������ء�
	ʵ��ʹ��ʱ��Ҫ���ر��࣬������onInit�¼��а��Զ���ĺ�����

Author: ���

Date: 2011.12.14

Update: 
2011.12.20
�������޸�Ϊ�������

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
	/**��ʼ��������ű������ص���������Ҫ��������ʵ��
	*/
	virtual bool onInit(){ return true; }
	virtual bool onClear(){ return true; }
	
	/**ִ�нű��е�ȫ�ֺ���
	@desc �÷���ֻ�ܵ�������������������ȫ�ֺ���
	*/
	virtual bool executeGlobalFunction( const std::string & name ){return true;}
	
	/**ִ�нű��е�ȫ�ֺ���
	@desc �÷�������ȫ�ֺ���,������bool����
	*/
	virtual bool executeGlobalFunction( const std::string & name , bool & ret ){return true;}
	
	/**ִ�нű��к���,����һ��Ҫ����ȫ�ֺ���
	*/
	virtual bool executeFunction( const std::string & name ){return true;}

	/**ִ�нű��к���,������bool����
	*/
	virtual bool executeFunction( const std::string & name , bool & ret ){return true;}
	
	/**�����ļ���ִ��
	*/
	virtual bool executeFile( const std::string & fileName ){return true;}
protected:
	bool m_bEnable; //��¼��ǰ�Ƿ��ǳ�ʼ�����״̬�����Ϊfalse�����к��������С�
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
