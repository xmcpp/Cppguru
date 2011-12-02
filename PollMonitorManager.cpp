#include "pch.h"
#include "PollMonitorManager.h"
#include "PollMonitorObject.h"
#include "StringConverter.h"

template<> PollMonitorManager* Singleton<PollMonitorManager>::ms_Singleton	= 0;

PollMonitorManager::PollMonitorManager()
{
	MessageDispatcher::getSingleton().addListener( this );
}

PollMonitorManager::~PollMonitorManager()
{
	MessageDispatcher::getSingleton().removeListener( this );
}

void PollMonitorManager::addPollMonitor( PollMonitorObject * object )
{
	if (!object) return;

	m_set.insert( object );
}

void PollMonitorManager::removePollMonitor( PollMonitorObject * object )
{
	if (!object) return;

	setItor it = m_set.find( object );
	if ( it != m_set.end() )
	{
		m_set.erase( it );
	}
}

void PollMonitorManager::clearAllPollMonitor()
{
	m_set.clear();
}

void PollMonitorManager::update( float time )
{
	for ( setItor it = m_set.begin() ; it != m_set.end() ; it++ )
	{
		(*it)->update( time );
	}
}

void PollMonitorManager::ReceiveMessage(unsigned int messageType , ParameterSet& messageParam)
{
	if( messageType == MD_TIME_FRAMETICK )
	{
		//表示每帧的事件
		float val = StringConverter::parseFloat( messageParam.GetValue( "interval" ) );
		
		//获取帧间隔以后调用更新
		update( val );
	}
}