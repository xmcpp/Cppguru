#ifndef _MESSAGEQUENEPROCESSOR_HPP_
#define _MESSAGEQUENEPROCESSOR_HPP_ 

#pragma once

#include "ThreadBase.h"
#include "BaseDefine.h"
#include "RingBuffer.h"

/** ��Ϣ��������߳���
@class MessageQueneProcessor

@remarks
	������ThreadBase�̳У�ʵ�ַ������������Ϣ�ַ��Ĺ����̡߳�

@note
	�����еķ������̰߳�ȫ�ġ�

@author ���

@date 2009-09-15

*/

class MessageQueneProcessor : public ThreadBase
{
public:
	///Ĭ�Ϲ��캯��
	MessageQueneProcessor();

	///Ĭ����������
	virtual ~MessageQueneProcessor(); 

public:
	/**�����¼��ӿ�
	@remarks
		��Ϣ�������Ӷ�����ȡ����Ϣ�����øýӿ��е�onMessageProcess�������������¼�����ĳ�����
	*/
	class QueneProcessorListener
	{
	public:
		virtual bool onMessageProcess( const MessageData & data ) = 0;
	};

public:
	/**�����¼�������
	@remarks
		������Ϣ��������ͨ�����������Ƿ����̿�ʼ����
	
	@param bRun ��ʾ�Ƿ��������� trueΪ�������У�falseΪ��������ͣ
	*/
	bool startProcessor( bool bRun = true );

	/**�ָ���Ϣ����������
	@remarks
		�ָ���Ϣ���������У�һ������Ϣ��������ͣ����Ե��ñ������ָ�����
	*/
	bool resumeProcessor();

	/**�ָ���Ϣ����������
	@remarks
		��ͣ��Ϣ���������У�ֻ���ڴ�����һ����Ϣ����ͣ�����ñ���������¼һ��
		״̬���ڴ����굱ǰ��Ϣ������������ͣ״̬������ͨ������resumeProcessor
		�ָ�����״̬
	*/
	bool suspendProcessor();

	/**ֹͣ��Ϣ����������
	@remarks
		ֹͣ��Ϣ���������У��÷������ú�ֹͣ�����������̣������ڵ���startProcessor����
		����������ֹͣ�������ڴ�����һ����Ϣ����Ч�������Ϣ�����л���������Ϣ��ᱻ����
	*/
	bool stopProcessor();
	
	/**����Ϣ����β�����һ����Ϣ
	@remarks
		��������ʵ��ʱ����Դ�����������������

	@param data �ȴ��������Ϣ���������
	@param pCurrentMsgCount ����Ϊָ�룬��������Ϊ��ǰ��Ϣ���������ж���ʣ��δ�������Ϣ����Ŀ�ϰ�����ǰ
							������ӵ�һ�������Ƿ���false��
	*/
	bool addMessage( const MessageData & data , uint32_t * pCurrentMsgCount );
	
	/**��õ�ǰδ������Ϣ����Ŀ
	*/
	int32_t getMessageCount();

	/**���ûص������ַ
	*/
	void setQueneProcessorListener( QueneProcessorListener * pListener );

private:
	
	/**�����������ڲ�ʹ�ã����̵߳���
	*/
	virtual bool onProcess();
private:
	///��Ϣ���еĶ���
	std::deque<MessageData> m_msgQuene;
	
	///ͬ������ؼ����Ķ���
	CRITICAL_SECTION m_section;

	///ͬ�������źŵƵĶ���,����źŵ����ڱ�ʾ��ǰ��Ϣ��������Ϣ����Ŀ����ʼ��Ϊ0����ʾû����Ϣ
	///��ִ���������Ϣ������һ��ֵ
	HANDLE m_semaphore;

	///�ص������ַ����
	QueneProcessorListener * m_listener;

	//����������
	RingBuffer				m_msgDataBuff;
};

#endif //_MESSAGEQUENEPROCESSOR_HPP_
