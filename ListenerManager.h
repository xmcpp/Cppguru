/***********************************
������ģʽģ�����

Author: ����

Date: 2010.8.20

Update: 2010.12.22 �Ľ��˵���ģʽ��غ����������ݾɰ汾  by ����
************************************/

#ifndef Listener_h_h_h
#define Listener_h_h_h


template<typename T>
class ListenerManager
{
public:

	typedef T* TPtr;
	typedef std::set<TPtr> ListenerSet;
	typedef typename ListenerSet::iterator ListenerIterator;	///�����߼�������

	/**���캯��*/
	ListenerManager(){}
	/**��������*/
	~ListenerManager()
	{
		removeAllListener();
	}

	/**���һ���µļ�����
	@param pListener ������ָ��
	*/
	void addListener(TPtr pListener)
	{
		ListenerIterator itr = mListeners.find(pListener);

		if (itr != mListeners.end())
			mListeners.erase(itr);
		else
			mListeners.insert(pListener);
	}

	/**�Ƴ�һ��������
	@param pListener ������ָ��
	*/
	void removeListener(TPtr pListener)
	{
		ListenerIterator itr = mListeners.find(pListener);

		if (itr != mListeners.end())
			mListeners.erase(itr);
	}

	/**�Ƴ�ȫ��������
	*/
	void removeAllListener()
	{
		mListeners.clear();
	}


	/** @name ����ģʽ��ؽӿ�*/
	//@{

	//�Ƽ�ʹ��-���ǲ���Ƕ��ʹ�ã����ڵ������������������ֵ����˱����firstListener�������������
	T* firstListener()
	{
		T* pListener = NULL;
		mCurrentListenerIterator = mListeners.begin();
		if (mCurrentListenerIterator != mListeners.end())
		{
			pListener = *mCurrentListenerIterator;
		}

		return pListener;
	}

	T* nextListener()
	{
		T* pListener = NULL;
		mCurrentListenerIterator++;
		if (mCurrentListenerIterator != mListeners.end())
		{
			pListener = *mCurrentListenerIterator;
		}

		return pListener;
	}



	//���Ƽ�ʹ�� ,���µ��������������������ҪǶ�׵���ʱʹ��,ҲΪ�˼��ݾɰ汾

	ListenerIterator Begin()
	{
		return mListeners.begin();
	}
	ListenerIterator End()
	{
		return mListeners.end();
	}

	//@}

private:
	ListenerSet						mListeners;				///�����߼�
	ListenerIterator				mCurrentListenerIterator;		//��ǰ�����ߵ�����
};
#endif