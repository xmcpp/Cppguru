/**********************************************************************
�������������

Desc:������������������Ѿ����������ж������󣬲����𴴽������Ը���ɾ��

Author: ���

Date: 2011.12.21

Update: 
2011.12.29
ʹ�䲻��Ϊ����,��TriggerManagerͳһ����
***********************************************************************/
#ifndef __ACTIONOBJECTMANAGER_H__
#define __ACTIONOBJECTMANAGER_H__

#include "MapManager.h"

class IActionObject;
class ActionObjectManager : public MapManager<IActionObject>
{
public:
	ActionObjectManager(){}
	~ActionObjectManager(){}
public:
	bool addActionObject( IActionObject * object );
	IActionObject * getActionObject( const std::string & name );
	bool removeActionObject( IActionObject * object , bool bDestory = false );
	bool removeActionObject( const std::string & name , bool bDestory = false );
	void removeAllActionObject( bool bDestory = false );
};

#endif //__ACTIONOBJECTMANAGER_H__
