/**********************************************************************
动作对象管理器

Desc:动作对象管理器管理已经创建的所有动作对象,它不负责创建,但在清除
时负责删除所有动作对象.

Author: 徐淼

Date: 2011.12.21

Update: 
***********************************************************************/
#ifndef __ACTIONOBJECTMANAGER_H__
#define __ACTIONOBJECTMANAGER_H__

#include "Singleton.h"

class IActionObject;
class ActionObjectManager : public Singleton<ActionObjectManager>
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
