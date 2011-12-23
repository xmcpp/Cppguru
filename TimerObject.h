#ifndef __TIMEROBJECT_H__
#define __TIMEROBJECT_H__

class TimerListener;

class ITimer
{
public:
	ITimer( const std::string & name );
	virtual ~ITimer();
	enum TimerState { TIMER_STOP , TIMER_RUNNING , TIMER_PAUSE };
	struct FormatTimeStruct
	{
		unsigned int m_hours;
		unsigned int m_minutes;
		unsigned int m_seconds;
		unsigned int m_millSeconds;
	};
public:
	virtual void start(){}
	virtual void pause(){}
	virtual void stop(){}
	virtual void resume(){}
	virtual void reset(){}

	virtual void update( float time ){}
	void addListener( TimerListener * listener );
	void removeListener( TimerListener * listener );
	void clearAllListener(){ m_timerSet.clear(); }

	void setName( const std::string & name ){ m_name = name; }
	std::string & getName(){ return m_name; }
	TimerState getState() { return m_timerState;}

protected:
	void timeFormat( unsigned long time , FormatTimeStruct & data );
protected:
	std::string m_name;
	std::set< TimerListener * > m_timerSet;
	typedef std::set< TimerListener * >::iterator timerSetItor;
	TimerState m_timerState;
};

class TimerListener
{
public:
	TimerListener(){}
	virtual ~TimerListener(){}
public:
	virtual void onStart( ITimer * timer ){}
	virtual void onStop( ITimer * timer ){}
	virtual void onPause( ITimer * timer ){}
	virtual void onResume( ITimer * timer ){}
};

#endif //__TIMEROBJECT_H__
