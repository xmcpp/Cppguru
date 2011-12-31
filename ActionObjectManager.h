/**********************************************************************
动作对象管理器

Desc:动作对象管理器管理已经创建的所有动作对象，不负责创建但可以负责删除

Author: 徐淼

Date: 2011.12.21

Update: 
2011.12.29
使其不成为单件,由TriggerManager统一管理
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
