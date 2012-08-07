#include "stdafx.h"
#include "MessageQueneManager.h"
#include "MessageQueneProcessor.h"

MessageQueneManager::MessageQueneManager()
:m_processorCount(0)
{

}

MessageQueneManager::~MessageQueneManager()
{
	destroyAll();
}

MessageQueneProcessor * MessageQueneManager::createMessageQueneProcessor( const std::string & name )
{
	MessageQueneProcessor * pProcessor = NULL;

	processorMap::iterator it = m_processorMap.find( name );
	if( it != m_processorMap.end() )
		pProcessor = it->second;
	else
	{
		pProcessor = new MessageQueneProcessor();
		m_processorMap.insert( std::make_pair( name , pProcessor ) );
		m_processorCount++;
	}
	return pProcessor;
}

MessageQueneProcessor * MessageQueneManager::getMessageQueneProcessor( const std::string & name )
{
	processorMap::iterator it = m_processorMap.find( name );

	if( it != m_processorMap.end() )
		return it->second;
	else
		return NULL;
}

uint32_t MessageQueneManager::getMessageQueneProcessorCount()
{
	return m_processorCount;
}

void MessageQueneManager::destroyMessageQueneProcessor( const std::string & name )
{
	processorMap::iterator it = m_processorMap.find( name );
	if( it != m_processorMap.end() )
	{
		delete it->second;
		m_processorMap.erase( it );
		m_processorCount--;
	}
}

void MessageQueneManager::destroyAll()
{
	for( processorMap::iterator it = m_processorMap.begin() , itEnd = m_processorMap.end() ; it != itEnd ; it++ )
	{
		delete it->second;
	}
	m_processorMap.clear();
	m_processorCount = 0;
}

bool MessageQueneManager::messageDispatch( const MessageData & msgData )
{
	//暂时还没有完成，需要处理转发逻辑
	if( m_processorCount < 1 )
		return true;

	m_processorMap.begin()->second->addMessage( msgData , NULL );

	return true;
}
