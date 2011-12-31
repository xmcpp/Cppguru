#include "pch.h"
#include "TestActionObject.h"

TestActionObject::TestActionObject( const std::string & name )
:IActionObject( name ),m_testState(false)
{

}

bool TestActionObject::excute()
{
	m_testState = true;
	return true;
}