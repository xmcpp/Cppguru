#include "pch.h"
#include "StringConverter.h"
#include "ParameterSet.h"

ParameterSet ParameterSet::EmptyParameterSet;

ParameterSet::ParameterSet(void)
{
}

ParameterSet::~ParameterSet(void)
{
}

bool ParameterSet::HasValue(const std::string& name)
{
	ParameterMapItr itr = mParameterMap.find(name);
	if (itr != mParameterMap.end())
	{
		return true;
	}
	return false;
}

void ParameterSet::SetValue(const std::string& name , const std::string& value)
{
	mParameterMap[name] = value;
}

std::string ParameterSet::GetValue(const std::string& name)
{
	ParameterMapItr itr = mParameterMap.find(name);
	if (itr != mParameterMap.end())
	{
		return itr->second;
	}
	return "";
}

void ParameterSet::SetObject(const std::string& name , void * pObject)
{
	int iPtr = (int)pObject;
	std::string strPtr = StringConverter::toString(iPtr);
	SetValue(name , strPtr);
}
void* ParameterSet::GetObject(const std::string& name)
{
	std::string strPtr = GetValue(name);
	if (strPtr=="")
	{
		return NULL;
	}

	int iPtr = StringConverter::parseInt(strPtr);
	return (void*)iPtr;
}

void ParameterSet::Clear()
{
	mParameterMap.clear();
}

ParameterSet::ConstParameterMapItr ParameterSet::Begin() const
{
	return mParameterMap.begin();
}
ParameterSet::ConstParameterMapItr ParameterSet::End() const
{
	return mParameterMap.end();
}