/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-03

* 简要描述: Singleton
			SingletonS（线程安全）
				
				Singleton(S)是用于定义单例模式的数据结构，可以使用它定义任意类型的
				唯一实例。

			注意：!!!不可使用在两个库之间，否则不会保证是一个实例，可能会产生两个以上的实例!!!
* 修改记录:

*****************************************************************************/
#pragma once
#include "../core/Def.h"
#include <mutex>

namespace nb{

template<class T>
class NB_API Singleton
{
public:
	static T *instance()
	{
		static T *t = nullptr;
		if(!t)	t = new T();
		return t;
	}
};

template<class T>
class SingletonS
{
public:
	static T *instance()
	{
		static T *t = nullptr;
		static std::mutex lock;
		//加一层判断，减少lock消耗
		if(!t)
		{
			lock.lock();
			if(!t)	t = new T();
			lock.unlock();
		}
		return t;
	}

};

}
