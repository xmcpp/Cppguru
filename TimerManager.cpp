#include "pch.h"
#include "TimerManager.h"
#include "EventMonitorObject.h"

template<> TimerManager* Singleton<TimerManager>::ms_Singleton	= 0;

TimerManager::TimerManager()
{
	m_eventMonitorObj = new EventMonitorObject("TimerManager_Used");
	m_eventMonitorObj->init();
	//m_eventMonitorObj->setMonitorEvent( )
}

TimerManager::~TimerManager()
{
	m_eventMonitorObj->clear();
	delete m_eventMonitorObj;
	m_eventMonitorObj = NULL;
}