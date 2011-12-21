#include "pch.h"
#include "ScriptActionObject.h"
#include "ScriptSystem.h"

ScriptActionObject::ScriptActionObject( const std::string & name )
:IActionObject(name)
{

}

ScriptActionObject::~ScriptActionObject()
{

}

bool ScriptActionObject::excute()
{
	bool ret = false;
	bool result = false;
	ScriptSystem * sys = ScriptSystemManager::getSingleton().getScriptSystem();
	
	if( !sys ) return ret;
	
	if( !sys->executeFunction( m_funName , result ) ) return ret;
	
	return result;
}
