#include "stdafx.h"
#include "NetworkCoreFactory.h"
#include "RaknetNetworkCore.h"

template<> NetworkCoreFactory * Singleton<NetworkCoreFactory>::ms_Singleton	= 0;

NetworkCoreFactory::~NetworkCoreFactory()
{
	for( coreSet::iterator it = m_coreSet.begin() , itEnd = m_coreSet.end() ; it != itEnd ; it++ )
	{
		delete ( *it );
	}
	m_coreSet.clear();

}

NetworkCore * NetworkCoreFactory::createNetworkCore( CORE_TYPE type )
{
	NetworkCore * pCore = NULL;

	switch ( type )
	{
	case BASERAKNET:
		pCore = new RaknetNetworkCore();
		break;
	case BASEIOCP:
		pCore = NULL;
		break;
	default:
		pCore = NULL;
	}

	//����
	if( pCore )
		m_coreSet.insert( pCore );

	return pCore;
}

void NetworkCoreFactory::destroyNetworkCore( NetworkCore * pCore )
{
	if( !pCore )
		return;
	
	//�Ӽ�����ɾ��
	m_coreSet.erase( pCore );
	
	//ɾ������
	delete pCore;
}