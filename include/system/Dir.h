/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Dir
				
				文件夹。用来描述系统文件夹节点的数据结构
				

* 修改记录:

*****************************************************************************/
#pragma once
#include "String.h"

namespace nb{ namespace System{

class Dir
{
public:
	bool Exists() const;

public:
	Dir();

	//构建一个Dir，它指向绝对路径absolute
	Dir(const nb::System::String &absolute);

public:
	//文件夹是否存在
	static bool IsExists();
};

}}

