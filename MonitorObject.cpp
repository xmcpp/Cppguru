#include "pch.h"
#include "MonitorObject.h"
#include "StringConverter.h"

IMonitorObject::IMonitorObject( const std::string & name , bool bAutoReset )
:m_name(name),m_activeState(false),m_isEnable(false),m_isAutoReset(bAutoReset)
,m_enableDeferred(false),m_baseDeferredTime(0.0f),m_baseDeferredTimeRecord(0.0f)
{
	MessageDispatcher::getSingleton().addListener( this );
}

IMonitorObject::~IMonitorObject()
{
	MessageDispatcher::getSingleton().removeListener( this );
}

void IMonitorObject::enable( bool val , bool bDeferredStart , float deferredTime )
{
	if ( val == m_isEnable ) return;
	
	//��������ӳ���������ֱ���޸�״̬������
	if ( !bDeferredStart ) 
	{
		m_isEnable = !m_isEnable;
		return;
	}

	//��¼��Ҫ�ӳٵ�ʱ��
	m_baseDeferredTime = (deferredTime < 0.0f)?0.0f:deferredTime;

	//�����ӳ�
	m_enableDeferred = true;
	
}

void IMonitorObject::addListener( IMonitorEventListener * listener )
{
	m_listenerSet.insert(listener);
}

void IMonitorObject::removeListener( IMonitorEventListener * listener )
{
	listenerSetItor itor = m_listenerSet.find( listener );
	if ( itor != m_listenerSet.end() )
	{
		m_listenerSet.erase( itor );
	}
}

void IMonitorObject::clearAllListener()
{
	m_listenerSet.clear();
}

void IMonitorObject::trigger()
{
	if( !m_isEnable ) return;
	
	if( !m_activeState )
	{
		m_activeState = true;
		sendAlarmMsg();
		
		//�Ƿ��Զ���λ
		if ( m_isAutoReset )
		{
			unTrigger(); //ִ�и�λ����
		}
	}
}

void IMonitorObject::unTrigger()
{
	if( !m_isEnable ) return;

	if( m_activeState )
	{
		m_activeState = false;
		sendSilenceMsg();
	}
}

void IMonitorObject::sendAlarmMsg()
{
	for ( listenerSetItor itor = m_listenerSet.begin() ; itor != m_listenerSet.end() ; itor++ )
	{
		(*itor)->onAlarmActive( this );
	}
}

void IMonitorObject::sendSilenceMsg()
{
	for ( listenerSetItor itor = m_listenerSet.begin() ; itor != m_listenerSet.end() ; itor++ )
	{
		(*itor)->onSilenceActive( this );
	}
}

void IMonitorObject::ReceiveMessage(unsigned int messageType , ParameterSet& messageParam)
{
	if ( !m_enableDeferred ) return;

	if ( messageType == MD_TIME_FRAMETICK )
	{
		m_baseDeferredTimeRecord += StringConverter::parseFloat( messageParam.GetValue("interval") );

		if ( m_baseDeferredTimeRecord >= m_baseDeferredTime )
		{
			m_isEnable = !m_isEnable;

			//ֹͣ�ӳټ��״̬
			stopDeferredState();
		}	
	}
}

void IMonitorObject::stopDeferredState()
{
	if ( !m_enableDeferred ) return;
	
	m_enableDeferred = false;
	m_baseDeferredTimeRecord = 0.0f;
	m_baseDeferredTime = 0.0f;
}