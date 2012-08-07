#ifndef _NETWORKCOREFACTORY_H_
#define _NETWORKCOREFACTORY_H_

#include "Singleton.h"
#include "NetworkCoreInterface.h"

class NetworkCore;

/** ������Ķ��󴴽�����
@class NetworkCoreFactory

@remarks
	����ฺ��������Ķ���Ĵ��������١��û������ڴ���ʱѡ�����������������Ķ���
	�����ǵ�����

@note
	Ŀǰֻ֧�ֻ���Raknet���ĵģ�δ�������ӻ���IOCP���ĵ�������Ķ���

@author ���

@date 2009-09-19

*/

class NetworkCoreFactory : public Singleton<NetworkCoreFactory>
{
public:
	///���캯��
	NetworkCoreFactory(){};
	
	///��������
	~NetworkCoreFactory();
public:
	///�������Դ����ĺ�������
	enum CORE_TYPE { BASERAKNET , BASEIOCP };
public:
	/**����������Ķ���
	@remarks
		���ø÷�������ָ����������Ķ�������������Ķ�����������ض���Ĵ����������ϲ�Ӧ��
		��˵����͸���ģ����ж��������NetworkCoreinterface�еĽӿڽ��в���

	@param type Ҫ����������Ķ�������ͣ�Ŀǰֻ��BASERAKNET��Ч

	@return ���ش����ɹ���������Ķ���ָ��
	*/
	NetworkCore * createNetworkCore( CORE_TYPE type );

	/**ɾ��������Ķ���
	@remarks
		���ø÷���ɾ��������Ķ���

	@param type Ҫɾ����������Ķ���ָ��

	*/
	void destroyNetworkCore( NetworkCore * pCore );

private:
	///���ڱ����Ѿ������ĺ��Ķ���������ʱɾ��
	std::set<NetworkCore*> m_coreSet;
	typedef std::set<NetworkCore*> coreSet;
};

#endif //_NETWORKCOREFACTORY_H_
