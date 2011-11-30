/***********************************
触发器

Author: 苗琳

Date: 2010.12.22

Update: 
************************************/
#ifndef Trigger_h
#define Trigger_h

#include "ParameterSet.h"
#include "MessageTypeDef.h"

//前置声明

class IConditionObject;
class IActionObject;

/** 触发器
@remark 
	触发器有三部分组成，事件驱动器，条件器，动作器
	其中事件驱动器由C++完成，脚本只要激活不同的事件驱动器即可，
	条件器和动作器都绑定为lua脚本中的某个函数
	当事件驱动器触发后，会执行条件器函数，若条件器返回true，则继续执行对应的动作器
	
	事件驱动器分两类：
	UpdateDriver 更新驱动器 每桢更新时就会触发
	MessageDriver 消息驱动器 若系统产生了该驱动器等待的事件，则触发
*/
class Trigger
{
public:
	Trigger(void);
	Trigger(const std::string& name);
	virtual ~Trigger(void);

	/** 获得触发器的名称*/
	virtual const std::string& GetName();

	/** 激活/禁止 当前触发器
	@remark 最高优先权，该触发器若被禁止，
	所有类型的事件驱动器将停止触发,但是仍可以调用Execute 强制执行动作器or条件器
	@param bEnable 传入true 激活触发器 传false禁止触发器
	*/
	virtual void Enable(bool bEnable);

	/** 当前触发器是否处于激活状态*/
	virtual bool IsEnable();

	/** 获得当前触发器缓存中的值
	@remark 脚本通过该函数获取一些触发器关心的数据,如消息参数
	@param name 参数的名称
	@return 参数的string 值
	*/
	virtual std::string GetValue(const std::string& name);

	/** 设置当前触发器缓存中的值
	@remark 脚本通过该函数设置一些触发器关心的数据，如消息参数
	@param name 参数的名称
	@param value 缓存中的值
	*/
	virtual void SetValue(const std::string& name , const std::string& value);

	/** 设置当前触发器缓存中的对象参数值
	@param name 该对象参数的名称
	@param pObject 该对象的指针
	*/
	virtual void SetObject(const std::string& name , void* pObject);

	/** 获得当前触发器缓存中的对象参数值
	@param name 该对象参数的名称
	@return 该对象参数的void指针,如不存在，返回NULL
	*/
	virtual void* GetObject(const std::string& name);

	/** 激活/禁止 更新事件驱动器
	@param bEnable true为激活,false为禁止
	@param fInterval 每次触发的间隔时间 , 若要每桢触发则设为0
	*/
	virtual void EnableUpdateDriver(bool bEnable , float fInterval = 0.0f);

	/** 激活/禁止 消息事件驱动器
	@param bEnable true为激活,false为禁止
	@param messageType 消息驱动器等待触发的事件类型
	*/
	virtual void EnableMessageDriver(bool bEnable , unsigned int messageType = 0);

	/** 是否激活了更新事件驱动器*/
	virtual bool IsEnableUpdateDriver();
	/** 是否激活了消息事件驱动器*/
	virtual bool IsEnableMessageDriver();
	
	/** 更新事件驱动器*/
	virtual void Update(float timeSinceLastFrame);

	/** 消息事件驱动器*/
	virtual void ReceiveMessage(unsigned int messageType , const ParameterSet& messageParameter);

	/** 添加一个条件器脚本函数并关联一个动作器脚本函数
	@param ConditionFunctionName 条件器脚本函数名称   为空则默认不检测条件，
	支持table嵌套中的函数 如  table1.subtable.functionA
	支持多个条件器函数，以空格隔开如 table1.subfunctionA table2.subfunctionB
	@param ActionFunctionName 动作器脚本函数名称  为空则默认不执行任何动作，支持table嵌套中的函数 如  table1.subtable.functionA
	*/
	virtual void AddConditionalAction(const std::string& ConditionFunctionName , const std::string& ActionFunctionName);

	/** 删除条件器和它相关联的动作器
	@param ConditionFunctionName 条件器脚本函数名称
	*/
	virtual void RemoveConditionalAction(const std::string& ConditionFunctionName);

	/** 执行触发器的动作
	@param bConditional 为true则检查条件后执行动作器,为false则忽略条件直接执行动作器
	*/
	virtual void Execute(bool bConditional = true);
private:

	class ActionInfo
	{
	public:
		std::string ConditionFunctionName;
		std::string ActionFunctionName;
		bool bBufferMode;	//只在缓冲器列表中起作用，用来标识该内容是缓冲删除还是缓冲添加,true为添加，false为删除
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


	/** 处理添加删除缓冲器
	@remark 由于在脚本中添加删除条件器，C++并不知情，
	有可能在遍例条件器时被脚本破坏了迭代器，所以添加删除全部缓存到单独的列表中，
	由更新时或执行后统一处理。
	*/
	void HandleAddDeleteBuffer();

	std::string mName;
	ParameterSet mValueSet;
	std::vector<ActionInfo> mActionList;
	std::vector<ActionInfo> mAddDeleteBuffer;	//添加删除缓冲器

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