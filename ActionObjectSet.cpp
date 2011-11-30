#include "pch.h"
#include "ActionObjectSet.h"

bool ActionObjectSet::init()
{
	m_actionSet.clear();
	return true;
}

bool ActionObjectSet::excute()
{
	for( actionSetItor it = m_actionSet.begin(); it != m_actionSet.end() ; it++ )
	{
		(*it)->excute();
	}
	return true;
}

bool ActionObjectSet::clear()
{
	m_actionSet.clear();
	return true;
}

void ActionObjectSet::addActionObject( IActionObject * object )
{
	if ( !object ) return;

	m_actionSet.insert( object );
}

void ActionObjectSet::removeActionObject( IActionObject * object )
{
	actionSetItor itor = m_actionSet.find( object );
	if ( itor != m_actionSet.end() )
	{
		m_actionSet.erase( itor );
	}
}

void ActionObjectSet::clearAllActionObject()
{
	m_actionSet.clear();
}