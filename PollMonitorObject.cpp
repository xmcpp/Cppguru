#include "pch.h"
#include "PollMonitorObject.h"
#include "StringConverter.h"

bool PollMonitorObject::init()
{
	return true;
}

bool PollMonitorObject::clear()
{
	return true;
}

void PollMonitorObject::enable( bool val )
{
	IMonitorObject::enable(val);
	
	//Çå¿ÕÀÛ¼ÓÖµ
	m_lastTime = 0.0f;
}

void PollMonitorObject::ReceiveMessage(unsigned int messageType , ParameterSet& messageParam)
{
	IMonitorObject::ReceiveMessage( messageType , messageParam );

	if ( !m_isEnable ) return;

	if ( messageType == MD_TIME_FRAMETICK )
	{
		m_lastTime += StringConverter::parseFloat( messageParam.GetValue("interval") );

		if ( m_lastTime >= m_interVal )
		{
			if ( onCheck() )
				trigger();

			m_lastTime = 0.0f;
		}	
	}
}