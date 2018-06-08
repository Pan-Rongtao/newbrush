/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec4
				
				描述维度为4的浮点型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/Vec.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec4 : public Vec
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

	//返回w分量的引用
	float &W();
	const float &W() const;

	//返回xy分量
	Vec2 XY() const;

	//返回yz分量
	Vec2 YZ() const;

	//返回zw分量
	Vec2 ZW() const;

	//返回xyz分量
	Vec3 XYZ() const;

	//返回yzw分量
	Vec3 YZW() const;

public:
	//构建一个Vec4，它的坐标为(0.0, 0.0, 0.0, 0.0)
	Vec4();

	//构建一个Vec4，它的坐标为(x, y, z, w);
	Vec4(float x, float y, float z, float w);

	//从Vec2构建一个Vec4
	Vec4(const Vec2 &xy, const Vec2 &zw);

	//从Vec2构建一个Vec4
	Vec4(float x, const Vec2 &yz, float w);

	//从Vec2构建一个Vec4
	Vec4(float x, float y, const Vec2 &zw);

	//从Vec3构建一个Vec4
	Vec4(const Vec3 &xyz, float w);

	//从Vec3构建一个Vec4
	Vec4(float x, const Vec3 &yzw);
};

}}
