/***********************************
������

Author: ����

Date: 2010.12.22

Update: 
************************************/
#ifndef ParameterSet_h
#define ParameterSet_h

#include <map>

/** ������
@remarks 
	ʵ�����޸�������ȡ�ͱ���Ĺ���
*/
class ParameterSet
{
public:
	static ParameterSet EmptyParameterSet;

	ParameterSet(void);
	~ParameterSet(void);
	
	/** �����Ƿ����
	@param name �ò���������
	@return trueΪ���ڣ�falseΪ������
	*/
	bool HasValue(const std::string& name);

	/** ���ò���
	@param name �ò���������
	@param value �ò�����ֵ
	*/
	void SetValue(const std::string& name , const std::string& value);

	/** ��ò���ֵ
	@param name �ò���������
	@return �ò�����ֵ,�粻���ڣ����� empty string
	*/
	std::string GetValue(const std::string& name);
	
	/** ���ö������ֵ
	@param name �ö������������
	@param pObject �ö����ָ��
	*/
	void SetObject(const std::string& name , void* pObject);

	/** ��ö������ֵ
	@param name �ö������������
	@return �ö��������voidָ��,�粻���ڣ�����NULL
	*/
	void* GetObject(const std::string& name);

	/** ������в���*/
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