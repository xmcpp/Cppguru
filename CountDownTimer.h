#ifndef __COUNTDOWNTIMER_H__
#define __COUNTDOWNTIMER_H__

#include "TimerObject.h"

class CountDownTimer : public ITimer
{
public:
	CountDownTimer( const std::string & name );
	virtual ~CountDownTimer(){}
};

#endif //__COUNTDOWNTIMER_H__
