/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec3B
				
				描述维度为3的布尔型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/VecB.h"
#include "math/Vec2B.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec3B : public VecB
{
public:
	//返回x分量的引用
	bool &X();
	const bool &X() const;

	//返回y分量的引用
	bool &Y();
	const bool &Y() const;

	//返回z分量的引用
	bool &Z();
	const bool &Z() const;

	//返回xy分量
	Vec2B XY() const;

	//返回yz分量
	Vec2B YZ() const;

public:
	//构建一个Vec3B，它的坐标为(0.0, 0.0, 0.0)
	Vec3B();

	//构建一个Vec3B，它的坐标为(x, y, z)
	Vec3B(bool x, bool y, bool z);

	//从一个Vec2B构建一个Vec3B
	Vec3B(const Vec2B &xy, bool z);

	//从一个Vec2B构建一个
	Vec3B(bool x, const Vec2B &yz);
};

}}
