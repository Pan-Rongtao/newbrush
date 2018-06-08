/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec2
				
				描述维度为2的浮点型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/Vec.h"

namespace nb{ namespace Math{


class NB_EXPORT Vec2 : public Vec
{
public:
	//返回x分量的引用
	float &X();
	const float &X() const;

	//返回y分量的引用
	float &Y();
	const float &Y() const;

	//标准化
	Vec2 Normalized() const;

	//叉乘（向量积）
	Vec2 CrossProduct(const Vec2 &other) const;

public:
	//构建一个Vec2对象, 它的坐标为（0.0, 0.0)
	Vec2();

	//从其他向量构建一个Vec2，它的坐标为(x, y)
	Vec2(float x, float y);

	Vec2(const Vec2 &other);
	~Vec2();
};


}}
