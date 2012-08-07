#include "stdafx.h"
#include "MessageQueneProcessor.h"

#define MAX_DATABUFFSIZE 10000

MessageQueneProcessor::MessageQueneProcessor()
:m_listener( NULL ) ,m_msgDataBuff( MAX_DATABUFFSIZE )
{
	//��ʼ���ؼ�������
	InitializeCriticalSection( &m_section );

	//�����źŵ�
	m_semaphore = CreateSemaphore( NULL , 0 , 10000 , NULL );
}

MessageQueneProcessor::~MessageQueneProcessor()
{
	//ɾ���ؼ�������
	DeleteCriticalSection( &m_section );

	//ɾ���źŵ�
	CloseHandle( m_semaphore );
}

bool MessageQueneProcessor::startProcessor( bool bRun )
{
	return ThreadBase::createThread( bRun );
}

bool MessageQueneProcessor::resumeProcessor()
{
	return ThreadBase::resumeThread();
}

bool MessageQueneProcessor::suspendProcessor()
{
	return ThreadBase::suspendThread();
}

bool MessageQueneProcessor::stopProcessor()
{
	return ThreadBase::closeThread();
}

bool MessageQueneProcessor::addMessage( const MessageData & data , uint32_t * pCurrentMsgCount )
{
	//����һ�ݣ���Ϊ����Ҫ�޸���data�ĵ�ַ���ܴ�����У�������һ��ǳ�����޷����⣬���մ���
	//���л�Ҫ����һ�顣�������˻������洢������Ч����Ӧ�������������İ������...
	
	MessageData tmpData = data; 

	EnterCriticalSection( &m_section );
	
	//�����ݵ���buff��,������µ�data��ַ�������������
	tmpData.data = m_msgDataBuff.pushBack( tmpData.data , tmpData.size );
	if( tmpData.data == NULL )
	{
		//��ʾ���ݻ����Ѿ����ˣ��޷�����������
		LeaveCriticalSection( &m_section );
		return false; 
	}
	m_msgQuene.push_back( tmpData );

	//�����źŵƵ�ֵ
	ReleaseSemaphore( m_semaphore , 1 , ( long * )pCurrentMsgCount );
	
	LeaveCriticalSection( &m_section );
	
	if( pCurrentMsgCount )
		++(*pCurrentMsgCount); //���ӵ�ǰ��ӵ������Ϣ�ļ���

	return true;
}

int32_t MessageQueneProcessor::getMessageCount()
{
	EnterCriticalSection( &m_section );

	int32_t count = (int32_t)m_msgQuene.size();

	LeaveCriticalSection( &m_section );

	return count;
}

void MessageQueneProcessor::setQueneProcessorListener( QueneProcessorListener * pListener )
{
	EnterCriticalSection( &m_section );

	m_listener = pListener;

	LeaveCriticalSection( &m_section );
}

///��������
bool MessageQueneProcessor::onProcess()
{
	while( 1 )
	{
		//��ȡ�źŵ�ȷ���Ƿ������ݿ���ʹ�ã�û������ʱ������
		WaitForSingleObject( m_semaphore , INFINITE ) ;

		//�Ӷ���ͷ��ȡ��һ����Ϣ���������Ӷ�����ȥ������Ϣ 
		EnterCriticalSection( &m_section );
		//�˴���һ��������Ϊ�˾���ӹؼ������˳�����Ϊ������Ϣ������̺����������Կ���һ�ݹ���������ʹ��
		MessageData data = m_msgQuene.front();
		m_msgQuene.pop_front();
		LeaveCriticalSection( &m_section );

		//��ȱ������Ϣ�Ĵ���...

		//����Ϣ���͸�Ӧ�ò㴦��
		if( m_listener )
			m_listener->onMessageProcess( data );

		//�����Ϣ��ռ�Ŀռ�
		EnterCriticalSection( &m_section );

		m_msgDataBuff.popFront( data.size );

		LeaveCriticalSection( &m_section );
	}
	
	
	return true;
}

