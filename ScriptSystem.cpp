#include "pch.h"
#include "ScriptSystem.h"

template<> ScriptSystemManager* Singleton<ScriptSystemManager>::ms_Singleton	= 0;

ScriptSystem::ScriptSystem()
:m_bEnable(false)
{

}

ScriptSystem::~ScriptSystem()
{

}

bool ScriptSystem::init()
{
	bool ret = onInit();
	if ( ret )
	{
		m_bEnable = true;
	}
	return ret;
}

bool ScriptSystem::clear()
{
	bool ret = onClear();
	m_bEnable = false;
	return ret;
}
