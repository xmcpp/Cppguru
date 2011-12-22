#ifndef __TIMERMANAGER_H__
#define __TIMERMANAGER_H__

#include "Singleton.h"

class CountDownTimer;
class SequenceTimer;

class ITimer
{
public:
	virtual void start();
	virtual void pause();
	virtual void stop();
	virtual void resume();
	virtual void reset();

	void setName( const std::string & name ){ m_name = name; }
	std::string & getName(){ return m_name; }
protected:
	std::string m_name;
};

class TimerManager : public Singleton<TimerManager>
{
public:
	TimerManager();
	~TimerManager();
public:
	CountDownTimer * createCountDownTimer( const std::string & name );
	SequenceTimer * createSequenceTimer( const std::string & name );
	void destroyTimer( ITimer * timer );
private:
	std::map<std::string , ITimer*> m_timerMap;
};

#endif //__TIMERMANAGER_H__
