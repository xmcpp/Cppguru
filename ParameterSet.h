/***********************************
参数集

Author: 苗琳

Date: 2010.12.22

Update: 
************************************/
#ifndef ParameterSet_h
#define ParameterSet_h

#include <map>

/** 参数集
@remarks 
	实现无限个参数获取和保存的功能
*/
class ParameterSet
{
public:
	static ParameterSet EmptyParameterSet;

	ParameterSet(void);
	~ParameterSet(void);
	
	/** 参数是否存在
	@param name 该参数的名称
	@return true为存在，false为不存在
	*/
	bool HasValue(const std::string& name);

	/** 设置参数
	@param name 该参数的名称
	@param value 该参数的值
	*/
	void SetValue(const std::string& name , const std::string& value);

	/** 获得参数值
	@param name 该参数的名称
	@return 该参数的值,如不存在，返回 empty string
	*/
	std::string GetValue(const std::string& name);
	
	/** 设置对象参数值
	@param name 该对象参数的名称
	@param pObject 该对象的指针
	*/
	void SetObject(const std::string& name , void* pObject);

	/** 获得对象参数值
	@param name 该对象参数的名称
	@return 该对象参数的void指针,如不存在，返回NULL
	*/
	void* GetObject(const std::string& name);

	/** 清除所有参数*/
	void Clear();

	typedef std::map<std::string , std::string> ParameterMap;
	typedef ParameterMap::iterator ParameterMapItr;
	typedef ParameterMap::const_iterator ConstParameterMapItr;

	ConstParameterMapItr Begin() const;
	ConstParameterMapItr End() const;

private:
	ParameterMap mParameterMap;
};

#endif //ParameterSet_h