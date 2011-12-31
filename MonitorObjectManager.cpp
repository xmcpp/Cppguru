#include "pch.h"
#include "MonitorObjectManager.h"
#include "MonitorObject.h"

bool MonitorObjectManager::addMonitorObject( IMonitorObject * object )
{
	bool ret = false;
	if ( !object ) return ret;

	return addObject( object->getName() , object )?true:false;
}

IMonitorObject * MonitorObjectManager::getMonitorObject( const std::string & name )
{
	return getObject( name );
}

bool MonitorObjectManager::removeMonitorObject( IMonitorObject * object , bool bDestory )
{
	if ( !object ) return false;
	return remove( object->getName() , bDestory );
}

bool MonitorObjectManager::removeMonitorObject( const std::string & name , bool bDestory )
{
	return remove( name , bDestory );
}

void MonitorObjectManager::removeAllMonitorObject( bool bDestory )
{
	removeAll( bDestory );
}
