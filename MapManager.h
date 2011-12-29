/***********************************
����map�����ĸ��������ģ��

Author: ����

Date: 2009.6.3

Update: 2010.12.22 �Ľ��˵���ģʽ��غ����������ݾɰ汾  by ����
************************************/

#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__


template<typename T >
class MapManager
{
public:
	typedef T* Tptr;		///����ָ����������
	typedef std::map<std::string, Tptr> ObjectMap;	///����������������
	typedef typename ObjectMap::iterator ObjectIterator;	///��������������
protected:
	ObjectMap m_ObjectMap;	///map����
	ObjectIterator mCurrentObjectIterator; ///��ǰ������


public:
	/**���캯��*/
	MapManager(){}
	/**��������*/
	virtual 	~MapManager()
	{
		
	}

	void addObject( const std::string& name , Tptr object )
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if( it != m_ObjectMap.end() ) return;
		
		m_ObjectMap.insert(std::make_pair(name,p));
	}


	/**��ö���
	@param name ��������
	@return ���ض���ָ��,������󲻴��ڣ�����null
	*/
	Tptr getObject(const std::string& name)
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			return it->second;
		}
		return NULL;
	}


	/**����һ������
	@param name ��������
	@return ���ض���ָ��
	*/
	bool  remove(const std::string& name , bool bDelete = false )
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			if( bDelete )
				delete it->second;
			m_ObjectMap.erase(it);
			return true;
		}

		return false;
	}

	/**�������ж���
	*/
	void  removeAll( bool bDelete = false )
	{
		if ( bDelete )
		{
			ObjectIterator	it = m_ObjectMap.begin();
			for(;it!=m_ObjectMap.end();++it)
			{
				delete it->second;
			}
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
};


#endif	//__MAPMANAGER_H__
