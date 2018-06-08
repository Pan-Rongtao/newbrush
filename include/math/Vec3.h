/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec3
				
				描述维度为3的浮点型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/Vec.h"
#include "math/Vec2.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec3 : public Vec
{
public:
	//返回x分量的引用
	float &X();
	const float &X() const;

	//返回y分量的引用
	float &Y();
	const float &Y() const;

	//返回z分量的引用
	float &Z();
	const float &Z() const;

	//返回xy分量
	Vec2 XY() const;

	//返回yz分量
	Vec2 YZ() const;

	//标准化
	Vec3 Normalized() const;

	//叉乘（向量积）
	Vec3 CrossProduct(const Vec3 &other) const;

public:
	//构建一个Vec3，它的坐标为(0.0, 0.0, 0.0)
	Vec3();

	//构建一个Vec3，它的坐标为(x, y, z)
	Vec3(float x, float y, float z);

	//从一个Vec2构建一个Vec3
	Vec3(const Vec2 &xy, float z);

	//从一个Vec2构建一个
	Vec3(float x, const Vec2 &yz);

public:
	Vec3 operator + (const Vec3 &other) const;
	Vec3 operator - (const Vec3 &other) const;
};


}}
