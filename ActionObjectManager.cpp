#include "pch.h"
#include "ActionObjectManager.h"
#include "ActionObject.h"

bool ActionObjectManager::addActionObject( IActionObject * object )
{
	bool ret = false;
	if ( !object ) return ret;
	
	if( !getActionObject( object->getName() ) ) return ret;
	
	m_actionObjectMap.insert( std::make_pair( object->getName() , object ) );
	return true;
}

IActionObject * ActionObjectManager::getActionObject( const std::string & name )
{
	mapItor it = m_actionObjectMap.find( name );
	if ( it == m_actionObjectMap.end() )
	{
		return NULL;
	}
	return it->second;
}

bool ActionObjectManager::removeActionObject( IActionObject * object )
{
	bool ret = false;
	if ( !object )	return ret;
	ret = removeActionObject( object->getName() );
	return ret;
}

bool ActionObjectManager::removeActionObject( const std::string & name )
{
	bool ret = false;
	mapItor it = m_actionObjectMap.find( name );
	if ( it != m_actionObjectMap.end() )
	{
		m_actionObjectMap.erase( it );
		ret = true;
	}
	return ret;
}

void ActionObjectManager::removeAll()
{
	for (mapItor it = m_actionObjectMap.begin() ; it != m_actionObjectMap.end() ; it++)
	{
		delete it->second;
	}
	m_actionObjectMap.clear();
}