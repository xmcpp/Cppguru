/**********************************************************************
��ʱ��������

Desc:��ʱ������������˶�ʱ���Ĵ�������������ٵĹ��ܡ�ͬʱ�ڲ���
�������ϵͳ�ĸ�����Ϣ������������ʱ���Ĺ�����

Author: ���

Date: 2011.12.22

Update: 
***********************************************************************/

#ifndef __TIMERMANAGER_H__
#define __TIMERMANAGER_H__

#include "Singleton.h"
#include <set>
#include "TimerObject.h"
#include "CountDownTimer.h"
#include "SequenceTimer.h"
#include "MessageDispatcher.h"

class CountDownTimer;
class SequenceTimer;
class TimerManager : public Singleton<TimerManager> , public IMessageReceiver
{
public:
	TimerManager();
	~TimerManager();
public:
	/**�����������Ƶĵ���ʱ��ʱ��
	@param name ��ʱ�����ƣ�ȫ��Ψһ
	@return ���صĶ�ʱ��ָ�룬������Ƴ�ͻ�򷵻�NULL
	*/
	CountDownTimer * createCountDownTimer( const std::string & name );

	/**�����������Ƶ�˳��ʱ��
	@param name ��ʱ�����ƣ�ȫ��Ψһ
	@return ���صĶ�ʱ��ָ�룬������Ƴ�ͻ�򷵻�NULL
	*/
	SequenceTimer * createSequenceTimer( const std::string & name );

	/**���ٶ�ʱ��*/
	void destroyTimer( ITimer * timer );

	/**�������ж�ʱ��*/
	void destroyAllTimer();
private:
	bool hasTimer( const std::string & name );
	void insertTimer( ITimer * timer );

	virtual void ReceiveMessage(unsigned int messageType , ParameterSet& messageParam);
private:
	std::map<std::string , ITimer*> m_timerMap;
	typedef std::map<std::string , ITimer*>::iterator timerMapItor;
};

#endif //__TIMERMANAGER_H__
