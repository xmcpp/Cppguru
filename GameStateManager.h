#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Singleton.h"

class GameState
{
public:
	GameState(){}
	virtual ~GameState(){}
public:
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void executeState( float time ) = 0;
};

class GameStateManager : public Singleton<GameStateManager>
{
public:
	GameStateManager();
	~GameStateManager();

public:
	void addState( const std::string & stateName , GameState * state );
	GameState * getState( const std::string & stateName );
	void clearAndDestroyAllState();
	void changeState( const std::string & stateName );
	void update( float time );
	void setCurrentState( GameState * state ){ m_curState = state;}
	
private:
	std::map<std::string , GameState *> m_stateMap;
	typedef std::map<std::string , GameState *> stateMap;

	GameState * m_curState ; //记录当前运行的状态
};

#endif //_GAMEMANAGER_H_
