/***********************************
������

Author: ����

Date: 2010.12.22

Update: 
************************************/
#ifndef Trigger_h
#define Trigger_h

#include "ParameterSet.h"
#include "MessageTypeDef.h"

//ǰ������

class IConditionObject;
class IActionObject;

/** ������
@remark 
	����������������ɣ��¼�����������������������
	�����¼���������C++��ɣ��ű�ֻҪ���ͬ���¼����������ɣ�
	�������Ͷ���������Ϊlua�ű��е�ĳ������
	���¼������������󣬻�ִ��������������������������true�������ִ�ж�Ӧ�Ķ�����
	
	�¼������������ࣺ
	UpdateDriver ���������� ÿ�����ʱ�ͻᴥ��
	MessageDriver ��Ϣ������ ��ϵͳ�����˸��������ȴ����¼����򴥷�
*/
class Trigger
{
public:
	Trigger(void);
	Trigger(const std::string& name);
	virtual ~Trigger(void);

	/** ��ô�����������*/
	virtual const std::string& GetName();

	/** ����/��ֹ ��ǰ������
	@remark �������Ȩ���ô�����������ֹ��
	�������͵��¼���������ֹͣ����,�����Կ��Ե���Execute ǿ��ִ�ж�����or������
	@param bEnable ����true ������� ��false��ֹ������
	*/
	virtual void Enable(bool bEnable);

	/** ��ǰ�������Ƿ��ڼ���״̬*/
	virtual bool IsEnable();

	/** ��õ�ǰ�����������е�ֵ
	@remark �ű�ͨ���ú�����ȡһЩ���������ĵ�����,����Ϣ����
	@param name ����������
	@return ������string ֵ
	*/
	virtual std::string GetValue(const std::string& name);

	/** ���õ�ǰ�����������е�ֵ
	@remark �ű�ͨ���ú�������һЩ���������ĵ����ݣ�����Ϣ����
	@param name ����������
	@param value �����е�ֵ
	*/
	virtual void SetValue(const std::string& name , const std::string& value);

	/** ���õ�ǰ�����������еĶ������ֵ
	@param name �ö������������
	@param pObject �ö����ָ��
	*/
	virtual void SetObject(const std::string& name , void* pObject);

	/** ��õ�ǰ�����������еĶ������ֵ
	@param name �ö������������
	@return �ö��������voidָ��,�粻���ڣ�����NULL
	*/
	virtual void* GetObject(const std::string& name);

	/** ����/��ֹ �����¼�������
	@param bEnable trueΪ����,falseΪ��ֹ
	@param fInterval ÿ�δ����ļ��ʱ�� , ��Ҫÿ�崥������Ϊ0
	*/
	virtual void EnableUpdateDriver(bool bEnable , float fInterval = 0.0f);

	/** ����/��ֹ ��Ϣ�¼�������
	@param bEnable trueΪ����,falseΪ��ֹ
	@param messageType ��Ϣ�������ȴ��������¼�����
	*/
	virtual void EnableMessageDriver(bool bEnable , unsigned int messageType = 0);

	/** �Ƿ񼤻��˸����¼�������*/
	virtual bool IsEnableUpdateDriver();
	/** �Ƿ񼤻�����Ϣ�¼�������*/
	virtual bool IsEnableMessageDriver();
	
	/** �����¼�������*/
	virtual void Update(float timeSinceLastFrame);

	/** ��Ϣ�¼�������*/
	virtual void ReceiveMessage(unsigned int messageType , const ParameterSet& messageParameter);

	/** ���һ���������ű�����������һ���������ű�����
	@param ConditionFunctionName �������ű���������   Ϊ����Ĭ�ϲ����������
	֧��tableǶ���еĺ��� ��  table1.subtable.functionA
	֧�ֶ���������������Կո������ table1.subfunctionA table2.subfunctionB
	@param ActionFunctionName �������ű���������  Ϊ����Ĭ�ϲ�ִ���κζ�����֧��tableǶ���еĺ��� ��  table1.subtable.functionA
	*/
	virtual void AddConditionalAction(const std::string& ConditionFunctionName , const std::string& ActionFunctionName);

	/** ɾ������������������Ķ�����
	@param ConditionFunctionName �������ű���������
	*/
	virtual void RemoveConditionalAction(const std::string& ConditionFunctionName);

	/** ִ�д������Ķ���
	@param bConditional Ϊtrue����������ִ�ж�����,Ϊfalse���������ֱ��ִ�ж�����
	*/
	virtual void Execute(bool bConditional = true);
private:

	class ActionInfo
	{
	public:
		std::string ConditionFunctionName;
		std::string ActionFunctionName;
		bool bBufferMode;	//ֻ�ڻ������б��������ã�������ʶ�������ǻ���ɾ�����ǻ������,trueΪ��ӣ�falseΪɾ��
		bool operator   ==(const   ActionInfo   &info)
		{
			if (info.ConditionFunctionName == ConditionFunctionName && info.ActionFunctionName == ActionFunctionName)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};


	/** �������ɾ��������
	@remark �����ڽű������ɾ����������C++����֪�飬
	�п����ڱ���������ʱ���ű��ƻ��˵��������������ɾ��ȫ�����浽�������б��У�
	�ɸ���ʱ��ִ�к�ͳһ����
	*/
	void HandleAddDeleteBuffer();

	std::string mName;
	ParameterSet mValueSet;
	std::vector<ActionInfo> mActionList;
	std::vector<ActionInfo> mAddDeleteBuffer;	//���ɾ��������

	bool mEnable;
	bool mEnableUpdateDriver;
	bool mEnableMessageDriver;

	unsigned int mWaitReceiveMessageType;
	float mInterval;
	float mCurrentTime;

	std::map<std::string,IActionObject*> m_actionMap;
	std::map<std::string,IConditionObject*> m_conditionMap;
};

#endif //Trigger_h