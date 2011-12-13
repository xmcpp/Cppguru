#ifndef __SCRIPTSYSTEM_H__
#define __SCRIPTSYSTEM_H__

struct lua_State;

class ScriptSystem
{
public:
	ScriptSystem();
	~ScriptSystem();
public:

private:
	lua_State * m_state;
};

#endif //__SCRIPTSYSTEM_H__
