/***********************************
触发器管理器

Author: 苗琳

Date: 2010.12.22

Update: 
************************************/
#ifndef TriggerManager_h
#define TriggerManager_h

#include "Trigger.h"
#include "MapManager.h"
#include "MessageDispatcher.h"
#include "Singleton.h"

/** 触发器管理器
@remark 
	前置要求：MessageDispatcher类首先初始化
	严重警告：不要在条件器或者动作器中或者在TriggerManager遍例所有触发器时调用CreateTrigger,DestroyTrigger,DestroyAllTrigger方法
	它们将破坏迭代器。

	管理该类创建的触发器,将消息派发给激活了消息驱动器的触发器，
	将每桢更新时运行激活了更新驱动器的触发器
*/
class TriggerManager : public MapManager<Trigger> , public IMessageReceiver , public Singleton<TriggerManager>
{
public:
	TriggerManager(void);
	~TriggerManager(void);


	/** 创建触发器
	@param name 触发器的唯一名称
	@return 触发器指针
	*/
	Trigger* CreateTrigger(const std::string& name);

	/** 获得触发器
	@param name 触发器的唯一名称
	@return 触发器指针
	*/
	Trigger* GetTrigger(const std::string& name);


	/** 删除触发器
	@param name 触发器的唯一名称
	@return 为true 表示删除成功，为false表示没有找到触发器
	*/
	bool DestroyTrigger(const std::string& name);

	/** 删除所有触发器*/
	void DestroyAllTrigger();

	/** 是否存在指定触发器
	@param name 触发器的唯一名称
	@return 为true 表示有该触发器, 为false 表示没有该触发器
	*/
	bool HasTrigger(const std::string& name);

	/** 激活触发器
	@param name 触发器的唯一名称
	@return 为true 表示激活成功，为false表示没有该触发器
	*/
	bool EnableTrigger(const std::string& name);

	/** 禁用触发器
	@param name 触发器的唯一名称
	@return 为true 表示禁用成功，为false表示没有该触发器
	*/
	bool DisableTrigger(const std::string& name);

	/** 执行触发器(忽略条件)
	@remark 直接调用该触发器的动作函数
	@param name 触发器的唯一名称
	@return 为true 表示执行成功，为false表示没有该触发器
	*/
	bool ExecuteTrigger(const std::string& name);

	/** 执行触发器(检查条件)
	@remark 先调用条件器，如果条件检查通过则调用该触发器的动作函数
	@param name 触发器的唯一名称
	@return 为true 表示执行成功，为false表示没有该触发器
	*/
	bool ConditionalExecuteTrigger(const std::string& name);


	
	
	/** 更新
	@remark 每桢更新时,会运行激活了更新驱动器的触发器
	*/
	void Update(float timeSinceLastFrame);

	
	virtual void ReceiveMessage(unsigned int messageType , const ParameterSet& messageParam);

	/** 获得每桢时间
	@remark 该函数纯属为了脚本系统的效率，
	将更新时的桢间隔时间统一记录，需要该值的条件函数和动作函数才需要调用它
	*/
	float GetTimeSinceLastFrame();

private:
	float mTimeSinceLastFrame;
};
#endif //TriggerManager_h