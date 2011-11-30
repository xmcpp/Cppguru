#include"pch.h"
#include "GameStateManager.h"

template<> GameStateManager* Singleton<GameStateManager>::ms_Singleton	= 0;

GameStateManager::GameStateManager()
:m_curState(NULL)
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
			m_curState->exitState();
		}

		m_curState = itor->second;

		m_curState->enterState();
	}
	else
	{
		m_curState = NULL;
	}
}

void GameStateManager::update( float time )
{
	if( !m_curState )
	{
		return;
	}

	m_curState->executeState( time );
}

