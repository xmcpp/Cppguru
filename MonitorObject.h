/**********************************************************************
��ض���ӿ�

Desc:��ض���ӿ��Ǽ�ض���Ļ���,�ṩ�˼�ض���Ļ�����Ϊ����.
ͬʱ���ṩ�˼�ض���������ӿ�

Author: ���

Date: 2011.11.28

Update: 
***********************************************************************/

#ifndef __MONITOROBJECT_H__
#define __MONITOROBJECT_H__

#include <set>

class IMonitorObject;

/**monitor���¼������ӿ�
*
*/
class IMonitorEventListener
{
public:
	/**�����¼�
	@remark ��������ʱ�������¼�
	@param object �����¼��Ķ���ָ�룬��������߷����¼���Դ 
	*/
	virtual void onAlarmActive( IMonitorObject * object ){}

	/**�������¼�
	@remark ����������ʱ�������¼�
	@param object �����¼��Ķ���ָ�룬��������߷����¼���Դ 
	*/
	virtual void onSilenceActive(  IMonitorObject * object ){}
};

/**monitor�Ķ���ӿ�
*
*/
class IMonitorObject 
{
public:
	/**���캯��
	@param name ��ض��������,Ĭ��Ϊ��
	@param bAutoReset �Ƿ����Զ���λ����Ĭ��Ϊfalse
	*/
	IMonitorObject( const std::string & name = "" , bool bAutoReset = false );
	virtual ~IMonitorObject(){}

public:
	/**��ʼ�������*/
	virtual bool init(){ return true;}
	virtual bool clear(){ return true;}
	
	/**���úͻ������*/
	const std::string & getName(){ return m_name; }
	void setName( const std::string & name ){ m_name = name; }
	
	/**���úͻ���Ƿ��Զ���λ*/
	bool isAutoReset(){ return m_isAutoReset; }
	void setAutoReset( bool val ){ m_isAutoReset = val; }

	/**����/����Monitor����
	@param val trueΪ���ö���falseΪ���ö���
	*/
	virtual void enable( bool val ){ m_isEnable = val; }
	
	/**��ȡ�Ƿ�������״̬*/
	virtual bool isEnable() { return m_isEnable; }
	
	/**��ȡ�Ƿ񼤻��״̬
	@remark �����δ����״̬�ǻ���ģ�״ֻ̬����������֮�б仯
	*/
	virtual bool isAlarmed(){ return m_activeState; }
	
	/**��ȡ�Ƿ�δ�����״̬*/
	virtual bool isSilence(){ return !m_activeState; }
	
	/**����ͷ�����Monitor����
	@remark �÷��������ƹ����������ǿ�Ƽ���򷴼���Monitor�Ķ���
	�÷������Զ����ö���״̬������״̬���Դ�isAlarmed��isSilence������á�
	*/
	virtual void trigger();
	virtual void unTrigger();

	/**��������߹���*/
	void addListener( IMonitorEventListener * listener );
	void removeListener( IMonitorEventListener * listener );
	void clearAllListener();
protected:
	/**�����м����߷����¼�*/
	void sendAlarmMsg();
	void sendSilenceMsg();
protected:
	std::string m_name;
	std::set<IMonitorEventListener*> m_listenerSet;
	typedef std::set<IMonitorEventListener*>::const_iterator listenerSetItor;
	bool m_activeState; //�Ƿ񼤻��״̬λ
	bool m_isEnable;	//�Ƿ�����
	bool m_isAutoReset; //�Ƿ��Զ���λ�����Ƿ��м���������Զ���λ�Ĺ���,Ĭ��Ϊfalse�����Զ���λ
};


#endif //__MONITOROBJECT_H__
