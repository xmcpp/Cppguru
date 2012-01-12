#include"pch.h"
#include "GameStateManager.h"

template<> GameStateManager* Singleton<GameStateManager>::ms_Singleton	= 0;

GameStateManager::GameStateManager()
:m_curState(NULL),m_needStartState(false)
{

}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::addState( const std::string & stateName , GameState * state )
{
	m_stateMap.insert( std::make_pair( stateName , state ) );
}

GameState * GameStateManager::getState( const std::string & stateName )
{
	stateMap::iterator it = m_stateMap.find( stateName );
	if( it == m_stateMap.end() )
		return NULL;

	return it->second;
}

void GameStateManager::clearAndDestroyAllState()
{
	for( stateMap::iterator it = m_stateMap.begin() , endIt = m_stateMap.end() ; it != endIt ; it++ )
	{
		delete it->second;
	}
	m_stateMap.clear();
}

void GameStateManager::changeState( const std::string & stateName )
{
	stateMap::const_iterator itor = m_stateMap.find( stateName );
	if( itor != m_stateMap.end() )
	{
		if( m_curState != itor->second && m_curState != 0 )
		{
			m_curState->endState();
		}

		m_curState = itor->second;
		m_needStartState = true;
	}
	else
	{
		m_curState = NULL;
	}
}

void GameStateManager::update( unsigned long millisecond )
{
	if( !m_curState )	return;

	if( m_needStartState )
	{
		m_curState->beginState();
		m_needStartState = false;
	}
	else
		m_curState->updateState( millisecond );
}

void GameStateManager::restartState()
{
	if( !m_curState ) return;
	
	m_curState->endState();
	m_needStartState = true;
}
