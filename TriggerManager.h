/***********************************
������������

Author: ����

Date: 2010.12.22

Update: 
************************************/
#ifndef TriggerManager_h
#define TriggerManager_h

#include "Trigger.h"
#include "MapManager.h"
#include "MessageDispatcher.h"
#include "Singleton.h"

/** ������������
@remark 
	ǰ��Ҫ��MessageDispatcher�����ȳ�ʼ��
	���ؾ��棺��Ҫ�����������߶������л�����TriggerManager�������д�����ʱ����CreateTrigger,DestroyTrigger,DestroyAllTrigger����
	���ǽ��ƻ���������

	������ഴ���Ĵ�����,����Ϣ�ɷ�����������Ϣ�������Ĵ�������
	��ÿ�����ʱ���м����˸����������Ĵ�����
*/
class TriggerManager : public MapManager<Trigger> , public IMessageReceiver , public Singleton<TriggerManager>
{
public:
	TriggerManager(void);
	~TriggerManager(void);


	/** ����������
	@param name ��������Ψһ����
	@return ������ָ��
	*/
	Trigger* CreateTrigger(const std::string& name);

	/** ��ô�����
	@param name ��������Ψһ����
	@return ������ָ��
	*/
	Trigger* GetTrigger(const std::string& name);


	/** ɾ��������
	@param name ��������Ψһ����
	@return Ϊtrue ��ʾɾ���ɹ���Ϊfalse��ʾû���ҵ�������
	*/
	bool DestroyTrigger(const std::string& name);

	/** ɾ�����д�����*/
	void DestroyAllTrigger();

	/** �Ƿ����ָ��������
	@param name ��������Ψһ����
	@return Ϊtrue ��ʾ�иô�����, Ϊfalse ��ʾû�иô�����
	*/
	bool HasTrigger(const std::string& name);

	/** �������
	@param name ��������Ψһ����
	@return Ϊtrue ��ʾ����ɹ���Ϊfalse��ʾû�иô�����
	*/
	bool EnableTrigger(const std::string& name);

	/** ���ô�����
	@param name ��������Ψһ����
	@return Ϊtrue ��ʾ���óɹ���Ϊfalse��ʾû�иô�����
	*/
	bool DisableTrigger(const std::string& name);

	/** ִ�д�����(��������)
	@remark ֱ�ӵ��øô������Ķ�������
	@param name ��������Ψһ����
	@return Ϊtrue ��ʾִ�гɹ���Ϊfalse��ʾû�иô�����
	*/
	bool ExecuteTrigger(const std::string& name);

	/** ִ�д�����(�������)
	@remark �ȵ���������������������ͨ������øô������Ķ�������
	@param name ��������Ψһ����
	@return Ϊtrue ��ʾִ�гɹ���Ϊfalse��ʾû�иô�����
	*/
	bool ConditionalExecuteTrigger(const std::string& name);


	
	
	/** ����
	@remark ÿ�����ʱ,�����м����˸����������Ĵ�����
	*/
	void Update(float timeSinceLastFrame);

	
	virtual void ReceiveMessage(unsigned int messageType , const ParameterSet& messageParam);

	/** ���ÿ��ʱ��
	@remark �ú�������Ϊ�˽ű�ϵͳ��Ч�ʣ�
	������ʱ������ʱ��ͳһ��¼����Ҫ��ֵ�����������Ͷ�����������Ҫ������
	*/
	float GetTimeSinceLastFrame();

private:
	float mTimeSinceLastFrame;
};
#endif //TriggerManager_h