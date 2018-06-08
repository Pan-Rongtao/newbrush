/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec2B
				
				描述维度为2的布尔型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/VecB.h"

namespace nb{ namespace Math{


class NB_EXPORT Vec2B : public VecB
{
public:
	//返回x分量的引用
	bool &X();
	const bool &X() const;

	//返回y分量的引用
	bool &Y();
	const bool &Y() const;

public:
	//构建一个Vec2B对象, 它的坐标为（0.0, 0.0)
	Vec2B();

	//从其他向量构建一个Vec2B，它的坐标为(x, y)
	Vec2B(bool x, bool y);

	Vec2B(const Vec2B &other);
	~Vec2B();
};


}}
