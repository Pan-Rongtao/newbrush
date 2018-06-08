/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec2I
				
				描述维度为2的整型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/VecI.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec2I : public VecI
{
public:
	//返回x分量的引用
	int &X();
	const int &X() const;

	//返回y分量的引用
	int &Y();
	const int &Y() const;

	//叉乘（向量积）
	Vec2I CrossProduct(const Vec2I &other) const;

public:
	//构建一个Vec2I对象, 它的坐标为（0.0, 0.0)
	Vec2I();

	//从其他向量构建一个Vec2I，它的坐标为(x, y)
	Vec2I(int x, int y);

	Vec2I(const Vec2I &other);
	~Vec2I();
};

}}
