/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 何平

* 编写日期: 2017-06

* 简要描述: 

* 修改记录:

*****************************************************************************/

#pragma once
#include "Global.h"

namespace nb{ namespace System{

template<class T>
class ValueAutoSwiter
{
public:
	ValueAutoSwiter(T &obj, const T & leaveValue)
		: m_valueObject(obj)
		, m_leaveValue(leaveValue)
	{
	}

	~ValueAutoSwiter()
	{
		m_valueObject = m_leaveValue;
	}

private:
	T &m_valueObject;
	T m_leaveValue;
};
}}
