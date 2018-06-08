/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-03

* 简要描述: Singleton
			SingletonS（线程安全）
				
				Singleton(S)是用于定义单例模式的数据结构，可以使用它定义任意类型的
				唯一实例。

* 修改记录:

*****************************************************************************/
#pragma once
#include "CriticalSection.h"

namespace nb{ namespace System{

template<class T>
class NB_EXPORT Singleton
{
public:
	static T *Current()
	{
		if(!t)	t = new T();
		return t;
	}

private:
	static T			*t;
};
template<class T> T *Singleton<T>::t = NULL;

template<class T>
class SingletonS
{
public:
	static T *Current()
	{
		//加一层判断，减少lock消耗
		if(!t)
		{
			lock.Lock();
			if(!t)	t = new T();
			lock.Unlock();
		}
		return t;
	}

private:
	static T					*t;
	static CriticalSection		lock;
};
template<class T> T *SingletonS<T>::t = NULL;
template<class T> CriticalSection SingletonS<T>::lock;

}}
