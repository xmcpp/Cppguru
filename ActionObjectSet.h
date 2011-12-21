/**********************************************************************
ActionObjectSet����

Desc:�Ƕ��������һ�֣��ṩ�������������ϲ���һ���Ĺ��ܡ���ִ��
Excuteʱ������ִ���ڲ����������ж�������

Author: ���

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
	/**��Ӷ�������
	@remark �����Ҫ���ϵĶ�������
	@param object ��Ҫ���ϵĶ���ָ��
	*/
	void addActionObject( IActionObject * object );

	/**ɾ����������
	@remark ɾ����Ҫ���ϵĶ�������
	@param object ��Ҫɾ���Ķ���ָ��
	*/
	void removeActionObject( IActionObject * object );
	void clearAllActionObject();
private:
	std::set<IActionObject*> m_actionSet;
	typedef std::set<IActionObject*>::iterator actionSetItor;
};

#endif //__ACTIONOBJECTSET_H__
