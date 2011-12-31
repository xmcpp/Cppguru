/**********************************************************************
Monitor���������

Desc:Monitor��������������Ѿ����������ж�������,�����𴴽������Ը���ɾ��
Author: ���

Date: 2011.12.31

Update: 
***********************************************************************/
#ifndef __MONITOROBJECTMANAGER_H__
#define __MONITOROBJECTMANAGER_H__

#include "MapManager.h"

class IMonitorObject;
class MonitorObjectManager : public MapManager<IMonitorObject>
{
public:
	MonitorObjectManager(){}
	~MonitorObjectManager(){}
public:
	bool addMonitorObject( IMonitorObject * object );
	IMonitorObject * getMonitorObject( const std::string & name );
	bool removeMonitorObject( IMonitorObject * object , bool bDestory = false );
	bool removeMonitorObject( const std::string & name , bool bDestory = false );
	void removeAllMonitorObject( bool bDestory = false );
};

#endif //__MONITOROBJECTMANAGER_H__
