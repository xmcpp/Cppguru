#ifndef __CPPSCRIPTSYSTEM_H__
#define __CPPSCRIPTSYSTEM_H__

#include "LuaScriptSystem.h"

class CppScriptSystem : public LuaScriptSystem
{
public:
	bool onInit();
	bool onClear();
};

#endif //__CPPSCRIPTSYSTEM_H__
