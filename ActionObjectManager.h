/**********************************************************************
�������������

Desc:������������������Ѿ����������ж�������,�������𴴽�,�������
ʱ����ɾ�����ж�������.

Author: ���

Date: 2011.12.21

Update: 
2011.12.29
ʹ�䲻��Ϊ����,��TriggerManagerͳһ����
***********************************************************************/
#ifndef __ACTIONOBJECTMANAGER_H__
#define __ACTIONOBJECTMANAGER_H__

#include "Singleton.h"

class IActionObject;
class ActionObjectManager
{
public:
	ActionObjectManager();
	~ActionObjectManager();

public:
	bool addActionObject( IActionObject * object );
	IActionObject * getActionObject( const std::string & name );
	bool removeActionObject( IActionObject * object );
	bool removeActionObject( const std::string & name );
	void removeAll();
private:
	std::map<std::string , IActionObject*>  m_actionObjectMap;
	typedef std::map<std::string , IActionObject*>::iterator mapItor;
};

#endif //__ACTIONOBJECTMANAGER_H__
