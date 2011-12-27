/**********************************************************************
��ʱ���ӿ�ָ��

Desc:��ʱ������Ļ���,�ṩ�����綨ʱ��״̬,��ʱ�������߹���Ĺ���,
ͬʱҲ�ṩ�˼�������ͨ�ú���.

Author: ���

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
	/**��ʱ�����ڲ�״̬���� ֹͣ�����к���ͣ����״̬ */
	enum TimerState { TIMER_STOP , TIMER_RUNNING , TIMER_PAUSE };

	/**����������ʽ��ʱ��Ľṹ�壬���Խ�����ת��ΪСʱ�����ӵȷ���*/
	struct FormatTimeStruct
	{
		unsigned int m_hours;
		unsigned int m_minutes;
		unsigned int m_seconds;
		unsigned int m_milliSeconds;
	};
protected: 
	/**ö�ٱ����ڲ�ʹ�ã���ÿ����ʱ����״̬�ı�ʱ��ͨ����������¼������࣬
	�ɻ�������������¼��������¼�ת�������иö�ʱ���ļ�����
	*/
	enum TimerMessage { TIMER_M_START , TIMER_M_STOP , TIMER_M_RESUME , TIMER_M_PAUSE , TIMER_M_UPDATE };
public:
	/**�����Ķ�ʱ����������*/
	virtual void start(){}
	virtual void pause(){}
	virtual void stop(){}
	virtual void resume(){}
	virtual void reset(){}
	virtual void update( float time ){}

	/**�����߹�����*/
	void addListener( TimerListener * listener );
	void removeListener( TimerListener * listener );
	void clearAllListener(){ m_timerSet.clear(); }
	
	/**��ʱ�����ƹ�����*/
	void setName( const std::string & name ){ m_name = name; }
	std::string & getName(){ return m_name; }

	/**��ȡ��ʱ��״̬����*/
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

/**��ʱ�������߽ӿ�

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

	/**�������ڶ�ʱ����ÿһ����ʱ������*/
	virtual void onSecond( ITimer * timer ){}
};

#endif //__TIMEROBJECT_H__
