/**********************************************************************
定时器接口指针

Desc:定时器对象的基类,提供了诸如定时器状态,定时器监听者管理的功能,
同时也提供了几个基本通用函数.

Author: 徐淼

Date: 2011.12.22

Update: 
***********************************************************************/
#ifndef __TIMEROBJECT_H__
#define __TIMEROBJECT_H__

class TimerListener;

class ITimer
{
public:
	ITimer( const std::string & name );
	virtual ~ITimer();
	/**定时器的内部状态包括 停止、运行和暂停三个状态 */
	enum TimerState { TIMER_STOP , TIMER_RUNNING , TIMER_PAUSE };

	/**用于描述格式化时间的结构体，可以将毫秒转换为小时、分钟等分量*/
	struct FormatTimeStruct
	{
		unsigned int m_hours;
		unsigned int m_minutes;
		unsigned int m_seconds;
		unsigned int m_milliSeconds;
	};
protected: 
	/**枚举变量内部使用，当每个定时器的状态改变时会通过发送这个事件给基类，
	由基类来处理这个事件，并将事件转发给所有该定时器的监听者
	*/
	enum TimerMessage { TIMER_M_START , TIMER_M_STOP , TIMER_M_RESUME , TIMER_M_PAUSE , TIMER_M_UPDATE };
public:
	/**基本的定时器操作函数*/
	virtual void start(){}
	virtual void pause(){}
	virtual void stop(){}
	virtual void resume(){}
	virtual void reset(){}
	virtual void update( float time ){}

	/**监听者管理函数*/
	void addListener( TimerListener * listener );
	void removeListener( TimerListener * listener );
	void clearAllListener(){ m_timerSet.clear(); }
	
	/**定时器名称管理函数*/
	void setName( const std::string & name ){ m_name = name; }
	std::string & getName(){ return m_name; }

	/**获取定时器状态函数*/
	TimerState getState() { return m_timerState;}
protected:
	void timeFormat( unsigned long time , FormatTimeStruct & data );
	void fireMessage( TimerMessage type );
protected:
	std::string m_name;
	std::set< TimerListener * > m_timerSet;
	typedef std::set< TimerListener * >::iterator timerSetItor;
	TimerState m_timerState;
};

/**定时器监听者接口

*/
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

	/**本方法在定时器满每一秒钟时被调用*/
	virtual void onSecond( ITimer * timer ){}
};

#endif //__TIMEROBJECT_H__
