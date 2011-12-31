#include "pch.h"
#include "ActionObjectManager.h"
#include "ActionObject.h"

bool ActionObjectManager::addActionObject( IActionObject * object )
{
	bool ret = false;
	if ( !object ) return ret;
		
	return addObject( object->getName() , object )?true:false;
}

IActionObject * ActionObjectManager::getActionObject( const std::string & name )
{
	return getObject( name );
}

bool ActionObjectManager::removeActionObject( IActionObject * object , bool bDestory )
{
	if ( !object ) return false;
	return remove( object->getName() , bDestory );
}

bool ActionObjectManager::removeActionObject( const std::string & name , bool bDestory )
{
	return remove( name , bDestory );
}

void ActionObjectManager::removeAllActionObject( bool bDestory )
{
	removeAll( bDestory );
}
