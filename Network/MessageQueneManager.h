#ifndef _MESSAGEQUENEMANAGER_H_
#define _MESSAGEQUENEMANAGER_H_ 

#include "BaseDefine.h"

class MessageQueneProcessor;

class MessageQueneManager
{
public:
	MessageQueneManager();
	~MessageQueneManager();

public:
	MessageQueneProcessor * createMessageQueneProcessor( const std::string & name );
	MessageQueneProcessor * getMessageQueneProcessor( const std::string & name ); 
	uint32_t getMessageQueneProcessorCount();

	void destroyMessageQueneProcessor( const std::string & name );
	void destroyAll();

	bool messageDispatch( const MessageData & msgData );
private:
	std::map< std::string , MessageQueneProcessor* > m_processorMap;
	typedef std::map< std::string , MessageQueneProcessor* > processorMap;

	uint32_t m_processorCount;
};

#endif //_MESSAGEQUENEMANAGER_H_
