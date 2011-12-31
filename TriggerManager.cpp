#include "pch.h"
#include "TriggerManager.h"

template<> TriggerManager* Singleton<TriggerManager>::ms_Singleton	= 0;

TriggerManager::TriggerManager()
:m_actObjMgr(NULL),m_bInit(false)
{
	
}

TriggerManager::~TriggerManager()
{

}

void TriggerManager::initTriggerSystem()
{
	m_actObjMgr = new ActionObjectManager();
	m_monitorObjMgr = new MonitorObjectManager();
	m_bInit = true;
}

void TriggerManager::uninitTriggerSystem()
{
	//删除所有对象
	m_actObjMgr->removeAllActionObject( true );
	m_monitorObjMgr->removeAllMonitorObject( true );
	
	//删除管理器
	delete m_actObjMgr;
	m_actObjMgr = NULL;
	delete m_monitorObjMgr;
	m_monitorObjMgr = NULL;

	m_bInit = false;
}

TriggerObject * TriggerManager::createTrigger( const std::string & name )
{
	if( !m_bInit ) return NULL;
	
	return addObject( name , new TriggerObject( name ) );
}

TriggerObject * TriggerManager::getTrigger( const std::string & name )
{
	if( !m_bInit ) return NULL;

	return getObject( name );
}

bool TriggerManager::destroyTrigger( const std::string & name )
{
	if( !m_bInit ) return false;

	return remove( name , true ); //自动删除
}