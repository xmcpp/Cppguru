#include "pch.h"
#include "TriggerManager.h" 

template<> TriggerManager* Singleton<TriggerManager>::ms_Singleton	= 0;

TriggerManager::TriggerManager(void)
:mTimeSinceLastFrame(0)
{
	MessageDispatcher::getSingleton().addListener(this);
}

TriggerManager::~TriggerManager(void)
{
	MessageDispatcher::getSingleton().removeListener(this);
}

Trigger* TriggerManager::CreateTrigger(const std::string& name)
{
	return Create(name , new Trigger(name));
}

Trigger* TriggerManager::GetTrigger(const std::string& name)
{
	return Get(name);
}

bool TriggerManager::DestroyTrigger(const std::string& name)
{
	return Destory(name);
}

void TriggerManager::DestroyAllTrigger()
{
	DestoryAll();
}

bool TriggerManager::HasTrigger(const std::string& name)
{
	return Has(name);
}

bool TriggerManager::EnableTrigger(const std::string& name)
{
	Trigger* pTrigger = GetTrigger(name);
	if (pTrigger)
	{
		pTrigger->Enable(true);
		return true;
	}

	return false;
}

bool TriggerManager::DisableTrigger(const std::string& name)
{
	Trigger* pTrigger = GetTrigger(name);
	if (pTrigger)
	{
		pTrigger->Enable(false);
		return true;
	}

	return false;
}

bool TriggerManager::ExecuteTrigger(const std::string& name)
{
	Trigger* pTrigger = GetTrigger(name);
	if (pTrigger)
	{
		pTrigger->Execute(false);
		return true;
	}

	return false;
}

bool TriggerManager::ConditionalExecuteTrigger(const std::string& name)
{
	Trigger* pTrigger = GetTrigger(name);
	if (pTrigger)
	{
		pTrigger->Execute();
		return true;
	}

	return false;
}

void TriggerManager::ReceiveMessage(unsigned int messageType , const ParameterSet& messageParam)
{
	ObjectIterator itr = BeginObjectIterator();
	while (itr!=EndObjectIterator())
	{
		Trigger* pTrigger = itr->second;
		if (pTrigger->IsEnable())
		{
			if (pTrigger->IsEnableMessageDriver())
			{
				pTrigger->ReceiveMessage(messageType , messageParam);
			}
		}

		itr++;
	}

}

void TriggerManager::Update(float timeSinceLastFrame)
{
	mTimeSinceLastFrame = timeSinceLastFrame;

	ObjectIterator itr = BeginObjectIterator();
	while (itr!=EndObjectIterator())
	{
		Trigger* pTrigger = itr->second;
		if (pTrigger->IsEnable())
		{
			if (pTrigger->IsEnableUpdateDriver())
			{
				pTrigger->Update(timeSinceLastFrame);
			}
		}

		itr++;
	}
}

float TriggerManager::GetTimeSinceLastFrame()
{
	return mTimeSinceLastFrame;
}