/**********************************************************************
定时器管理器

Desc:定时器提管理器供了定时器的创建、管理和销毁的功能。同时内部还
负责监听系统的更新信息，并来驱动定时器的工作。

Author: 徐淼

Date: 2011.12.22

Update: 
***********************************************************************/

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
	/**创建给定名称的倒计时定时器
	@param name 定时器名称，全局唯一
	@return 返回的定时器指针，如果名称冲突则返回NULL
	*/
	CountDownTimer * createCountDownTimer( const std::string & name );

	/**创建给定名称的顺序定时器
	@param name 定时器名称，全局唯一
	@return 返回的定时器指针，如果名称冲突则返回NULL
	*/
	SequenceTimer * createSequenceTimer( const std::string & name );

	/**销毁定时器*/
	void destroyTimer( ITimer * timer );

	/**销毁所有定时器*/
	void destroyAllTimer();
private:
	bool hasTimer( const std::string & name );
	void insertTimer( ITimer * timer );

	virtual void ReceiveMessage(unsigned int messageType , ParameterSet& messageParam);
private:
	std::map<std::string , ITimer*> m_timerMap;
	typedef std::map<std::string , ITimer*>::iterator timerMapItor;
};

#endif //__TIMERMANAGER_H__
