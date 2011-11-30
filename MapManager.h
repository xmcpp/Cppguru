/***********************************
����map�����ĸ��������ģ��

Author: ����

Date: 2009.6.3

Update: 2010.12.22 �Ľ��˵���ģʽ��غ����������ݾɰ汾  by ����
************************************/

#ifndef MapManager_h_h_h
#define MapManager_h_h_h


template<typename T >
class MapManager
{
public:
	typedef T* Tptr;		///����ָ����������
	typedef std::map<std::string, Tptr> ObjectMap;	///����������������
	typedef typename ObjectMap::iterator ObjectIterator;	///��������������
private:
	ObjectMap m_ObjectMap;	///map����
	ObjectIterator mCurrentObjectIterator; ///��ǰ������


public:
	/**���캯��*/
	MapManager(){}
	/**��������*/
	virtual 	~MapManager()
	{
		DestoryAll();
	}

	/**��������
	@param name ��������
	@param pExternalCreateObject ���ⲿ�����Ķ���ָ�룬���ΪNull��Ϊ�ڲ��������������ֵ��������ⲿ������ӽ�������
	@param bReplace ��������Ķ������Ѵ��ڣ��Ƿ��滻��trueΪ�滻��falseΪ�����Ѵ��ڵı���
	@return ���ش����Ķ���ָ��
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


	/**��ö���
	@param name ��������
	@return ���ض���ָ��,������󲻴��ڣ�����null
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


	/**���һ�������Ƿ����
	@param name ��������
	@return ������ڷ���true �����ڷ���false
	*/
	bool Has(const std::string& name)
	{
		if(m_ObjectMap.find(name)!=m_ObjectMap.end())
		{
			return true;
		}
		return false;
	}

	/**����һ������
	@param name ��������
	@return ���ض���ָ��
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

	/**�������ж���
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


	///////////////////////////////����ģʽ///////////////////////////////////////////

//�Ƽ���

	/*����map��ʼλ�õĵ�����
	@remark ����������++����
	*/
	ObjectIterator BeginObjectIterator()
	{
		return m_ObjectMap.begin();
	}
	/*����map����λ�õĵ�����
	@remark �����ж��Ƿ���ĩβ
	*/
	ObjectIterator EndObjectIterator()
	{
		return m_ObjectMap.end();
	}
	/*ͨ��ָ���ĵ�����ɾ������
	@param iterator Ҫɾ�������λ�õ�����
	*/
	ObjectIterator DestoryObjectByIterator(ObjectIterator iterator)
	{
		delete iterator->second;
		return m_ObjectMap.erase(iterator);
	}

//���Ƽ���,for old version
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