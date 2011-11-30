#include "pch.h"
#include "Trigger.h"
//#include "ScriptSystem.h"
//#include "ConditionObject.h"
#include <algorithm>


Trigger::Trigger(void)
:mEnable(false) , mEnableUpdateDriver(false) , mEnableMessageDriver(false)
{
	
}

Trigger::Trigger(const std::string& name)
	:mEnable(false) , mEnableUpdateDriver(false) , mEnableMessageDriver(false) , mName(name)
{
	
}

Trigger::~Trigger(void)
{
	
}

const std::string& Trigger::GetName()
{
	return mName;
}


void Trigger::Enable(bool bEnable)
{
	mEnable = bEnable;
}

bool Trigger::IsEnable()
{
	return mEnable;
}

void Trigger::EnableUpdateDriver(bool bEnable , float fInterval)
{
	mEnableUpdateDriver = bEnable;
	mInterval = fInterval;
	mCurrentTime = 0;
}

void Trigger::EnableMessageDriver(bool bEnable , unsigned int messageType)
{
	mEnableMessageDriver = bEnable;
	mWaitReceiveMessageType = messageType;
}

bool Trigger::IsEnableUpdateDriver()
{
	return mEnableUpdateDriver;
}

bool Trigger::IsEnableMessageDriver()
{
	return mEnableMessageDriver;
}

void Trigger::Update(float timeSinceLastFrame)
{
	mCurrentTime += timeSinceLastFrame;
	if (mCurrentTime>mInterval)
	{
		//timeSinceLastFrameֵ��ʱ����Ҫ�ģ����ǵ�Ч�����ﲻ���浽��������
		//��ֵ���浽TriggerManager�У��ű�����Ҫ������Ӧ������ȡ
		Execute();
		mCurrentTime = 0.0f;
	}
}

void Trigger::ReceiveMessage(unsigned int messageType , const ParameterSet& messageParameter)
{
	if (mWaitReceiveMessageType == messageType)
	{
		ParameterSet::ConstParameterMapItr itr = messageParameter.Begin();
		while (itr != messageParameter.End())
		{
			SetValue(itr->first , itr->second);
			itr++;
		}
		Execute();
	}
}

void Trigger::AddConditionalAction(const std::string& ConditionFunctionName , const std::string& ActionFunctionName)
{
	ActionInfo info;
	info.ConditionFunctionName = ConditionFunctionName;
	info.ActionFunctionName = ActionFunctionName;
	info.bBufferMode = true;
	
	std::vector<ActionInfo>::iterator itr = std::find(mActionList.begin() , mActionList.end() , info);
	if (itr==mActionList.end())
	{
		mAddDeleteBuffer.push_back(info);
	}
	
}

void Trigger::RemoveConditionalAction(const std::string& ConditionFunctionName)
{
	std::vector<ActionInfo>::iterator itr = mActionList.begin();
	while (itr!=mActionList.end())
	{
		if (ConditionFunctionName == itr->ConditionFunctionName)
		{
			itr->bBufferMode = false;
			mAddDeleteBuffer.push_back(*itr);
		}
		
		itr++;
	}
}


std::string Trigger::GetValue(const std::string& name)
{
	return mValueSet.GetValue(name);
}

void Trigger::SetValue(const std::string& name , const std::string& value)
{
	mValueSet.SetValue(name , value);
}

void Trigger::SetObject(const std::string& name , void * pObject)
{
	mValueSet.SetObject(name , pObject);
}
void* Trigger::GetObject(const std::string& name)
{
	return mValueSet.GetObject(name);
}

void Trigger::Execute(bool bConditional)
{
	//�ȴ�������
	HandleAddDeleteBuffer();

	std::vector<ActionInfo>::iterator itr = mActionList.begin();
	while (itr!=mActionList.end())
	{

		bool bResult = true;  //������ʧ��/�ɹ�

		if (bConditional)
		{
			/*if (itr->ConditionFunctionName.empty() == false)
			{
				//���������ѭ��,ֻҪ��һ������false�����ж�������ʧ��
				Ogre::StringVector functions = Ogre::StringUtil::split(itr->ConditionFunctionName , " ");
				Ogre::StringVector::iterator itr2 = functions.begin();
				while (itr2 != functions.end())
				{
					if(itr2->empty() == false)
					{
						//ִ���������ű�����
						//bResult = ScriptSystem::getSingleton().executeScriptFunctionEX(itr2->c_str() , this , "Trigger");
						//�������ж�Ϊ��
						if (!bResult)
						{
							break;
						}
					}

					itr2++;
				}
				
				if (!bResult)
				{
					itr++;
					continue;
				}

			}	*/

		}

		//ִ�ж������ű�����
		if (itr->ActionFunctionName.empty() == false)
		{
			//ScriptSystem::getSingleton().executeScriptFunctionEX(itr->ActionFunctionName , this , "Trigger");
		}
		
		
		itr++;
	}
	
}

void Trigger::HandleAddDeleteBuffer()
{
	if (mAddDeleteBuffer.empty()) return ;


	std::vector<ActionInfo>::iterator itr = mAddDeleteBuffer.begin();
	while (itr!=mAddDeleteBuffer.end())
	{
		if (itr->bBufferMode)
		{
			mActionList.push_back(*itr);
		}
		else
		{
			std::vector<ActionInfo>::iterator removeIter = mActionList.begin();
			while (removeIter!=mActionList.end())
			{
				if (itr->ConditionFunctionName == removeIter->ConditionFunctionName)
				{
					removeIter = mActionList.erase(removeIter);
					continue;
				}

				removeIter++;
			}
		}

		itr++;
	}

	mAddDeleteBuffer.clear();
}