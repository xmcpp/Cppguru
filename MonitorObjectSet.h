/**********************************************************************
���ϼ�ض���

Desc:�ṩ��ϼ�ض���Ĺ��ܡ����Խ�1..n����ض��󸴺ϳ�һ��������
��ض���ͬʱ�����������෽��ʹ�á�
1. ANDMonitorObject �ṩ�������Ӷ��󶼼���ʱ���������
2. ORMonitorObject �ṩֻҪ��һ���Ӷ��󱻼���ʱ���������

Author: ���

Date: 2011.11.30

Update: 
***********************************************************************/

#ifndef __MONITOROBJECTSET_H__
#define __MONITOROBJECTSET_H__

#include <set>
#include "MonitorObject.h"

class MonitorObjectSet : public IMonitorObject , public IMonitorEventListener
{
public:
	MonitorObjectSet(){}
	virtual ~MonitorObjectSet(){}

public:
	/**��ʼ�������*/
	virtual bool init();
	virtual bool clear();
	
	/**�¼���Ӧ����*/
	virtual void onAlarmActive( IMonitorObject * object );
	virtual void onSilenceActive(  IMonitorObject * object );

public:
	/**������MonitorObject*/
	void addMonitorObject( IMonitorObject * object );
	void removeMonitorObject( IMonitorObject * object );
	void clearAllMonitorObject();
protected:
	/**�ж��Ƿ�������Monitor���󶼷��ϼ����׼
	@remark �ú������麯������Ҫ�������أ�ʵ���Լ����ж�����
	@ret trueΪ�ǣ�falseΪ��
	*/
	virtual bool isAllActive(){ return false; }
protected:
	std::set<IMonitorObject*> m_monitorObjSet;
	typedef std::set<IMonitorObject*>::iterator monitorObjSetItor;
};


class ANDMonitorObject : public MonitorObjectSet
{
private:
	/**�ж��Ƿ�������Monitor���󶼷��ϼ����׼
	@remark ʵ�ֵ�������Monitor���󶼼���ʱ����True
	@ret trueΪ�ǣ�falseΪ��
	*/
	bool isAllActive();
};

class ORMonitorObject : public MonitorObjectSet
{
private:
	/**�ж��Ƿ�������Monitor���󶼷��ϼ����׼
	@remark ʵ�ֵ���1����Monitor���󼤻�ʱ�ͷ���True
	@ret trueΪ�ǣ�falseΪ��
	*/
	bool isAllActive();
};


#endif //__MONITOROBJECTSET_H__

