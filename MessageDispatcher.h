/***********************************
��Ϣ������

Author: ����

Date: 2010.12.22

Update: 
************************************/


#ifndef MessageDispatcher_h
#define MessageDispatcher_h

#include "ParameterSet.h"
#include "ListenerManager.h"
#include "Singleton.h"
#include "MessageTypeDef.h"


/** ��Ϣ����������ӿ�
@remark
	������Ϣ���շ�����Ϣ�������Ĺ�ϵ,��Ϣ���շ��п��������ڽű�ϵͳ��
Ҳ�п���������C++�е�ĳЩģ�飬��Ϣ������ͨ���ýӿ�ͳһ�����¼���
*/
class IMessageReceiver
{
public:
	/** ������Ϣ�ӿ�
	@param messageType ��Ϣ���ͱ�ʶ
	@param messageParam ��Ϣ����������
	*/
	virtual void ReceiveMessage(unsigned int messageType , const ParameterSet& messageParam){};
};



/** ��Ϣ������
@remark
	������Ϣ�ķ��ͣ����ȣ���ѯ������
������Ҫ����Ϣ��ģ�鶼��Ҫ�̳�IMessageReceiver�ӿڣ�
�����Լ�ָ��ͨ��addListener(this)ע�ᵽ����
*/
class MessageDispatcher : public ListenerManager<IMessageReceiver> , public Singleton<MessageDispatcher>
{
public:
	MessageDispatcher(void);
	~MessageDispatcher(void);

	/** ������Ϣ
	@remark ͬ��ģʽ���������͸�ÿ����Ϣ������
	@param messageType ��Ϣ���ͱ�ʶ
	@param messageParam ��Ϣ����������
	*/
	void SendMessage(unsigned int messageType , const ParameterSet& messageParam);

	/** Ͷ����Ϣ
	@remark �첽ģʽ,ֻ����ϢͶ�ݵ������У���ÿ����µ�ʱ���ڷ��͸�ÿ����Ϣ������
	@param messageType ��Ϣ���ͱ�ʶ
	@param messageParam ��Ϣ����������
	*/
	void PostMessage(unsigned int messageType , const ParameterSet& messageParam);

	void Update(float timeSinceLastFrame);

private:
	/** ��Ϣ�ṹ��
	@remark �ڲ�ά������Ϣ�ṹ��,��Ҫ��¼��Ϣ��ȫ����Ϣ�������б��еȴ�����
	*/
	class MessageInfo
	{
	public:
		///��Ϣ���ͱ�ʶ
		unsigned int type;
		///��Ϣ����������
		ParameterSet param;
	};

	///��Ϣ����
	std::list<MessageInfo> mMessageList;

};

#endif //MessageDispatcher_h