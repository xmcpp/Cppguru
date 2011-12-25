#include "pch.h"
#include "TimerManager.h"
#include "StringConverter.h"

template<> TimerManager* Singleton<TimerManager>::ms_Singleton	= 0;

TimerManager::TimerManager()
{
	MessageDispatcher::getSingleton().addListener( this );
}

TimerManager::~TimerManager()
{
	MessageDispatcher::getSingleton().removeListener( this );
	
	destroyAllTimer();
}

CountDownTimer * TimerManager::createCountDownTimer( const std::string & name )
{
	CountDownTimer * p = NULL;
	if ( !hasTimer( name ))
	{
		p = new CountDownTimer( name );
		m_timerMap.insert( std::make_pair( name , p ) );
	}
	
	return p;
}

SequenceTimer * TimerManager::createSequenceTimer( const std::string & name )
{
	SequenceTimer * p = NULL;
	if ( !hasTimer( name ))
	{
		p = new SequenceTimer( name );
		m_timerMap.insert( std::make_pair( name , p ) );
	}

	return p;
}

void TimerManager::destroyTimer( ITimer * timer )
{
	if ( !timer ) return;

	timerMapItor it = m_timerMap.find( timer->getName() );
	if( it == m_timerMap.end() )
		return ;

	delete it->second;
	m_timerMap.erase( it );
}

void TimerManager::destroyAllTimer()
{
	for ( timerMapItor it = m_timerMap.begin() ; it != m_timerMap.end() ; it++ )
	{
		delete it->second;
	}
	m_timerMap.clear();
}

void TimerManager::insertTimer( ITimer * timer )
{
	m_timerMap.insert( std::make_pair( timer->getName() , timer ) );
}

bool TimerManager::hasTimer( const std::string & name )
{
	timerMapItor it = m_timerMap.find( name );
	if( it == m_timerMap.end() )
		return false;
	return true;
}

void TimerManager::ReceiveMessage(unsigned int messageType , ParameterSet& messageParam)
{
	if( messageType == MD_TIME_FRAMETICK )
	{
		//表示每帧的事件
		float val = StringConverter::parseFloat( messageParam.GetValue( "interval" ) );

		for ( timerMapItor it = m_timerMap.begin(); it != m_timerMap.end() ; it++ )
		{
			it->second->update( val );
		}
	}
}