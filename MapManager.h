/***********************************
基于map容器的各类管理器模板

Author: 苗琳

Date: 2009.6.3

Update: 2010.12.22 改进了迭代模式相关函数，并兼容旧版本  by 苗琳
************************************/

#ifndef MapManager_h_h_h
#define MapManager_h_h_h


template<typename T >
class MapManager
{
public:
	typedef T* Tptr;		///对象指针类型声明
	typedef std::map<std::string, Tptr> ObjectMap;	///对象容器类型声明
	typedef typename ObjectMap::iterator ObjectIterator;	///对象容器迭代器
private:
	ObjectMap m_ObjectMap;	///map容器
	ObjectIterator mCurrentObjectIterator; ///当前迭代器


public:
	/**构造函数*/
	MapManager(){}
	/**析构函数*/
	virtual 	~MapManager()
	{
		DestoryAll();
	}

	/**创建对象
	@param name 对象名称
	@param pExternalCreateObject 从外部创建的对象指针，如果为Null则为内部创建对象，如果有值，则将这个外部对象添加进集合中
	@param bReplace 如果创建的对象名已存在，是否替换，true为替换，false为返回已存在的变量
	@return 返回创建的对象指针
	*/
	Tptr Create(const std::string& name,Tptr pExternalCreateObject = NULL, bool bReplace=true)
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			if(bReplace)
			{
				Destory(name);
			}
			else
			{
				return it->second;
			}
		}
		
		Tptr p = NULL;
		if (pExternalCreateObject)
		{
			p = pExternalCreateObject;
		}
		else
		{
			p = new T();
		}
		
		if (p)
		{
			m_ObjectMap.insert(std::make_pair(name,p));
		}
		
		return p;
	}


	/**获得对象
	@param name 对象名称
	@return 返回对象指针,如果对象不存在，返回null
	*/
	Tptr Get(const std::string& name)
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			return it->second;
		}
		return NULL;
	}


	/**检测一个对象是否存在
	@param name 对象名称
	@return 对象存在返回true 不存在返回false
	*/
	bool Has(const std::string& name)
	{
		if(m_ObjectMap.find(name)!=m_ObjectMap.end())
		{
			return true;
		}
		return false;
	}

	/**销毁一个对象
	@param name 对象名称
	@return 返回对象指针
	*/
	bool  Destory(const std::string& name)
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			delete it->second;
			m_ObjectMap.erase(it);
			return true;
		}

		return false;
	}

	/**销毁所有对象
	*/
	void  DestoryAll()
	{
		ObjectIterator	it = m_ObjectMap.begin();
		for(;it!=m_ObjectMap.end();++it)
		{
			delete it->second;
		}

		m_ObjectMap.clear();
	}


	///////////////////////////////迭代模式///////////////////////////////////////////

//推荐的

	/*返回map开始位置的迭代器
	@remark 迭代器可以++操作
	*/
	ObjectIterator BeginObjectIterator()
	{
		return m_ObjectMap.begin();
	}
	/*返回map结束位置的迭代器
	@remark 用来判断是否到了末尾
	*/
	ObjectIterator EndObjectIterator()
	{
		return m_ObjectMap.end();
	}
	/*通过指定的迭代器删除物体
	@param iterator 要删除物体的位置迭代器
	*/
	ObjectIterator DestoryObjectByIterator(ObjectIterator iterator)
	{
		delete iterator->second;
		return m_ObjectMap.erase(iterator);
	}

//不推荐的,for old version
	ObjectIterator firstObjectIterator()
	{
		mCurrentObjectIterator = m_ObjectMap.begin();
		return mCurrentObjectIterator;
	}

	ObjectIterator nextObjectIterator()
	{
		if (mCurrentObjectIterator!=m_ObjectMap.end())
		{
			mCurrentObjectIterator++;
		}
		
		return mCurrentObjectIterator;
	}

	Tptr getCurrentIteratorObject()
	{
		return mCurrentObjectIterator->second;
	}

	void DestoryCurrentIteratorObject()
	{
		delete mCurrentObjectIterator->second;
		m_ObjectMap.erase(mCurrentObjectIterator++);
	}

	bool hasMoreObject()
	{
		if (mCurrentObjectIterator==m_ObjectMap.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

};


#endif	