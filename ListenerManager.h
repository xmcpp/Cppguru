/***********************************
监听者模式模板基类

Author: 苗琳

Date: 2010.8.20

Update: 2010.12.22 改进了迭代模式相关函数，并兼容旧版本  by 苗琳
************************************/

#ifndef Listener_h_h_h
#define Listener_h_h_h


template<typename T>
class ListenerManager
{
public:

	typedef T* TPtr;
	typedef std::set<TPtr> ListenerSet;
	typedef typename ListenerSet::iterator ListenerIterator;	///监听者集迭代器

	/**构造函数*/
	ListenerManager(){}
	/**析构函数*/
	~ListenerManager()
	{
		removeAllListener();
	}

	/**添加一个新的监听者
	@param pListener 监听者指针
	*/
	void addListener(TPtr pListener)
	{
		ListenerIterator itr = mListeners.find(pListener);

		if (itr != mListeners.end())
			mListeners.erase(itr);
		else
			mListeners.insert(pListener);
	}

	/**移除一个监听者
	@param pListener 监听者指针
	*/
	void removeListener(TPtr pListener)
	{
		ListenerIterator itr = mListeners.find(pListener);

		if (itr != mListeners.end())
			mListeners.erase(itr);
	}

	/**移除全部监听者
	*/
	void removeAllListener()
	{
		mListeners.clear();
	}


	/** @name 迭代模式相关接口*/
	//@{

	//推荐使用-但是不能嵌套使用，即在迭代过程中其它对象又调用了本类的firstListener将造迭代器混乱
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



	//不推荐使用 ,以下迭代方法可以在特殊的需要嵌套迭代时使用,也为了兼容旧版本

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
	ListenerSet						mListeners;				///监听者集
	ListenerIterator				mCurrentListenerIterator;		//当前监听者迭代器
};
#endif