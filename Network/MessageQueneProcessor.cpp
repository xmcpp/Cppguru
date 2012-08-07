#include "stdafx.h"
#include "MessageQueneProcessor.h"

#define MAX_DATABUFFSIZE 10000

MessageQueneProcessor::MessageQueneProcessor()
:m_listener( NULL ) ,m_msgDataBuff( MAX_DATABUFFSIZE )
{
	//初始化关键区对象
	InitializeCriticalSection( &m_section );

	//创建信号灯
	m_semaphore = CreateSemaphore( NULL , 0 , 10000 , NULL );
}

MessageQueneProcessor::~MessageQueneProcessor()
{
	//删除关键区对象
	DeleteCriticalSection( &m_section );

	//删除信号灯
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
	//复制一份，因为下面要修改其data的地址才能存入队列，所以这一次浅拷贝无法避免，最终存入
	//队列还要拷贝一遍。但利用了缓冲区存储数据在效率上应该有所补偿，心安理得了...
	
	MessageData tmpData = data; 

	EnterCriticalSection( &m_section );
	
	//将数据导入buff中,并获得新的data地址，并存入队列中
	tmpData.data = m_msgDataBuff.pushBack( tmpData.data , tmpData.size );
	if( tmpData.data == NULL )
	{
		//表示数据缓存已经满了，无法接收新数据
		LeaveCriticalSection( &m_section );
		return false; 
	}
	m_msgQuene.push_back( tmpData );

	//增加信号灯的值
	ReleaseSemaphore( m_semaphore , 1 , ( long * )pCurrentMsgCount );
	
	LeaveCriticalSection( &m_section );
	
	if( pCurrentMsgCount )
		++(*pCurrentMsgCount); //增加当前添加的这个消息的计数

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

///主处理函数
bool MessageQueneProcessor::onProcess()
{
	while( 1 )
	{
		//获取信号灯确认是否有数据可以使用，没有数据时被阻塞
		WaitForSingleObject( m_semaphore , INFINITE ) ;

		//从队列头上取出一个消息拷贝，并从队列中去除该消息 
		EnterCriticalSection( &m_section );
		//此处做一个拷贝是为了尽快从关键区中退出，因为后续消息处理过程很漫长，所以拷贝一份供后续操作使用
		MessageData data = m_msgQuene.front();
		m_msgQuene.pop_front();
		LeaveCriticalSection( &m_section );

		//还缺管理消息的处理...

		//将消息发送给应用层处理
		if( m_listener )
			m_listener->onMessageProcess( data );

		//清除消息所占的空间
		EnterCriticalSection( &m_section );

		m_msgDataBuff.popFront( data.size );

		LeaveCriticalSection( &m_section );
	}
	
	
	return true;
}

