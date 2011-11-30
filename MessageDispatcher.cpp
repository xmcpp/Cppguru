#include "pch.h"
#include "MessageDispatcher.h"



template<> MessageDispatcher* Singleton<MessageDispatcher>::ms_Singleton	= 0;

MessageDispatcher::MessageDispatcher(void)
{
}

MessageDispatcher::~MessageDispatcher(void)
{
}

void MessageDispatcher::SendMessage(unsigned int messageType , const ParameterSet& messageParam)
{
	ListenerIterator itr = Begin();
	while (itr!=End())
	{
		(*itr)->ReceiveMessage(messageType , messageParam);
		itr++;
	}
}
void MessageDispatcher::PostMessage(unsigned int messageType , const ParameterSet& messageParam)
{
	MessageInfo info;
	info.type = messageType;
	info.param = messageParam;

	mMessageList.push_back(info);
}

void MessageDispatcher::Update(float timeSinceLastFrame)
{
	std::list<MessageInfo>::iterator itr = mMessageList.begin();
	while (itr!=mMessageList.end())
	{
		SendMessage(itr->type , itr->param);
		itr++;
	}

	mMessageList.clear();
}