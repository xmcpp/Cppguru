/**********************************************************************
��������ӿ�

Desc:��������ӿ��Ƕ�������Ļ���.�ýӿ��������������֮����ִ��
����Ϊ.

Author: ���

Date: 2011.11.28

Update: 
***********************************************************************/
#ifndef __ACTIONOBJECT_H__
#define __ACTIONOBJECT_H__

#include <set>

class IActionObject 
{
public:
	IActionObject( const std::string & name = "" )
		:m_name(name){}
	virtual ~IActionObject(){}
public:
	virtual bool init(){ return true; }
	virtual bool excute() = 0;
	virtual bool clear(){ return true; }
	const std::string & getName(){ return m_name; }
	void setName( const std::string & name ){ m_name = name; }
protected:
	std::string m_name;
};

#endif //__ACTIONOBJECT_H__


