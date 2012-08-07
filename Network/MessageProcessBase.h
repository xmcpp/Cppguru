#ifndef _MESSAGEPROCESSBASE_H_
#define _MESSAGEPROCESSBASE_H_

#include "utility/BaseDefine.h"
#include "Core/NetworkCoreInterface.h"
#include "Core/ServerLogManager.h"

class MessageProcessBase
{
public:
	virtual bool process( const MessageData & data ) = 0;
	void setNetworkCore( NetworkCore * pCore )
	{
		m_core = pCore; 
		m_mgr = pCore->getSessionManager();
	}
protected:
	NetworkCore * m_core;
	SessionManager * m_mgr;
};

#endif //_MESSAGEPROCESSBASE_H_
