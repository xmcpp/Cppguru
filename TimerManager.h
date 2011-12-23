#ifndef __TIMERMANAGER_H__
#define __TIMERMANAGER_H__

#include "Singleton.h"
#include <set>
#include "TimerObject.h"
#include "CountDownTimer.h"
#include "SequenceTimer.h"
#include "MessageDispatcher.h"

class CountDownTimer;
class SequenceTimer;
class TimerManager : public Singleton<TimerManager> , public IMessageReceiver
{
public:
	TimerManager();
	~TimerManager();
public:
	CountDownTimer * createCountDownTimer( const std::string & name );
	SequenceTimer * createSequenceTimer( const std::string & name );
	void destroyTimer( ITimer * timer );
private:
	bool hasTimer( const std::string & name );
	void insertTimer( ITimer * timer );

	virtual void ReceiveMessage(unsigned int messageType , ParameterSet& messageParam);
private:
	std::map<std::string , ITimer*> m_timerMap;
	typedef std::map<std::string , ITimer*>::iterator timerMapItor;
};

#endif //__TIMERMANAGER_H__
