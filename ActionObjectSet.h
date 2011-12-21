/**********************************************************************
ActionObjectSet对象

Desc:是动作对象的一种，提供将多个动作对象合并成一个的功能。当执行
Excute时会依次执行内部包含的所有动作对象。

Author: 徐淼

Date: 2011.11.28

Update: 
***********************************************************************/
#ifndef __ACTIONOBJECTSET_H__
#define __ACTIONOBJECTSET_H__

#include "ActionObject.h"
#include <set>

class ActionObjectSet : public IActionObject
{
public:
	ActionObjectSet( const std::string & name );
	virtual ~ActionObjectSet(){}
public:
	bool init();
	bool excute();
	bool clear();
	/**添加动作对象
	@remark 添加需要复合的动作对象
	@param object 需要复合的对象指针
	*/
	void addActionObject( IActionObject * object );

	/**删除动作对象
	@remark 删除需要复合的动作对象
	@param object 需要删除的对象指针
	*/
	void removeActionObject( IActionObject * object );
	void clearAllActionObject();
private:
	std::set<IActionObject*> m_actionSet;
	typedef std::set<IActionObject*>::iterator actionSetItor;
};

#endif //__ACTIONOBJECTSET_H__
