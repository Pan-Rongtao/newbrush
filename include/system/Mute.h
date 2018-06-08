/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-03

* 简要描述: Mute
				
				共享互斥体，用于解决不同进程获取线程间的资源访问问题

* 修改记录:

*****************************************************************************/
#pragma once
#include "Global.h"

namespace nb{ namespace System{

class Mute_Internal;
class NB_EXPORT Mute
{
public:
	//创建一个名字为name互斥体
	//如果互斥体已存在，将构建该互斥体的副本
	explicit Mute(const char *name);
	~Mute();

	//+1锁计数
	void Lock();

	//-1锁计数
	void Unlock();

public:
	//互斥体是否存在
	static bool IsExists(const char *name);

private:
	Mute_Internal	*m_internal;
};

}}
