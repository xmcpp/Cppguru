#include "pch.h"
#include "PollMonitorObject.h"

void PollMonitorObject::enable( bool val )
{
	IMonitorObject::enable(val);
	
	//Çå¿ÕÀÛ¼ÓÖµ
	m_lastTime = 0.0f;
}

void PollMonitorObject::update( float time )
{
	if ( !m_isEnable ) return;
	
	m_lastTime += time;
	
	if ( m_lastTime >= m_interVal )
	{
		if ( onCheck() )
			trigger();
		
		m_lastTime = 0.0f;
	}	
}
