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

class ValueAutoIncDec
{
public:
	ValueAutoIncDec(int &obj)
		: m_valueObject(obj)
	{
		m_valueObject++;
	}

	~ValueAutoIncDec()
	{
		m_valueObject--;
	}

private:
	int &m_valueObject;
};
}}
