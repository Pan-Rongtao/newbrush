/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec3I
				
				描述维度为3的整型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/VecI.h"
#include "math/Vec2I.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec3I : public VecI
{
public:
	//返回x分量的引用
	int &X();
	const int &X() const;

	//返回y分量的引用
	int &Y();
	const int &Y() const;

	//返回z分量的引用
	int &Z();
	const int &Z() const;

	//返回xy分量
	Vec2I XY() const;

	//返回yz分量
	Vec2I YZ() const;

	//叉乘（向量积）
	Vec3I CrossProduct(const Vec3I &other) const;

public:
	//构建一个Vec3I，它的坐标为(0.0, 0.0, 0.0)
	Vec3I();

	//构建一个Vec3I，它的坐标为(x, y, z)
	Vec3I(int x, int y, int z);

	//从一个Vec2I构建一个Vec3I
	Vec3I(const Vec2I &xy, int z);

	//从一个Vec2I构建一个
	Vec3I(int x, const Vec2I &yz);
};

}}
