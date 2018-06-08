/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2016-09

* 简要描述: CriticalSection
				
				临界区，用来描述线程访问界限的数据结构，
				一般而言，用作对不同线程对同一数据的同步读写操作
				每次Lock和Unlock都做计数增减。

* 修改记录:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace System{

class CriticalSection_Internal;
class NB_EXPORT CriticalSection
{
public:
	//+1锁计数
	void Lock();

	//-1锁计数
	void Unlock();

public:
	//构建一个临界区
	CriticalSection();
	~CriticalSection();

private:
	CriticalSection_Internal	*m_pInternal;
};

}}
