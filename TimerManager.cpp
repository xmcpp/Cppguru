#include "pch.h"
#include "TimerManager.h"
#include "EventMonitorObject.h"

template<> TimerManager* Singleton<TimerManager>::ms_Singleton	= 0;

TimerManager::TimerManager()
{
	
}

TimerManager::~TimerManager()
{
	
}