#ifndef __ACTIONOBJECTMANAGER_H__
#define __ACTIONOBJECTMANAGER_H__

#include "Singleton.h"

class IActionObject;
class ActionObjectManager : public Singleton<ActionObjectManager>
{
public:
	ActionObjectManager();
	~ActionObjectManager();

public:
	bool addActionObject( IActionObject * object );
	IActionObject * getActionObject( const std::string & name );
	bool removeActionObject( IActionObject * object );
	bool removeActionObject( const std::string & name );
	void removeAll();
private:
	std::map<std::string , IActionObject*> m_actionObjectMap;
	typedef std::map<std::string , IActionObject*>::iterator mapItor;
};

#endif //__ACTIONOBJECTMANAGER_H__
