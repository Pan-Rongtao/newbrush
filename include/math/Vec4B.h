/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec4
				
				描述维度为4的布尔型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/VecB.h"
#include "math/Vec2B.h"
#include "math/Vec3B.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec4B : public VecB
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

	//返回w分量的引用
	bool &W();
	const bool &W() const;

	//返回xy分量
	Vec2B XY() const;

	//返回yz分量
	Vec2B YZ() const;

	//返回zw分量
	Vec2B ZW() const;

	//返回xyz分量
	Vec3B XYZ() const;

	//返回yzw分量
	Vec3B YZW() const;

public:
	//构建一个Vec4B，它的坐标为(0.0, 0.0, 0.0, 0.0)
	Vec4B();

	//构建一个Vec4B，它的坐标为(x, y, z, w);
	Vec4B(bool x, bool y, bool z, bool w);

	//从Vec2B构建一个Vec4B
	Vec4B(const Vec2B &xy, const Vec2B &zw);

	//从Vec2B构建一个Vec4B
	Vec4B(bool x, const Vec2B &yz, bool w);

	//从Vec2B构建一个Vec4B
	Vec4B(bool x, bool y, const Vec2B &zw);

	//从Vec3B构建一个Vec4B
	Vec4B(const Vec3B &xyz, bool w);

	//从Vec3B构建一个Vec4B
	Vec4B(bool x, const Vec3B &yzw);
};

}}
