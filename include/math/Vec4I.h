/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec4I
				
				描述维度为4的整型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/VecI.h"
#include "math/Vec2I.h"
#include "math/Vec3I.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec4I : public VecI
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

	//返回w分量的引用
	int &W();
	const int &W() const;

	//返回xy分量
	Vec2I XY() const;

	//返回yz分量
	Vec2I YZ() const;

	//返回zw分量
	Vec2I ZW() const;

	//返回xyz分量
	Vec3I XYZ() const;

	//返回yzw分量
	Vec3I YZW() const;

public:
	//构建一个Vec4I，它的坐标为(0.0, 0.0, 0.0, 0.0)
	Vec4I();

	//构建一个Vec4I，它的坐标为(x, y, z, w);
	Vec4I(int x, int y, int z, int w);

	//从Vec2I构建一个Vec4I
	Vec4I(const Vec2I &xy, const Vec2I &zw);

	//从Vec2I构建一个Vec4I
	Vec4I(int x, const Vec2I &yz, int w);

	//从Vec2I构建一个Vec4I
	Vec4I(int x, int y, const Vec2I &zw);

	//从Vec3I构建一个Vec4I
	Vec4I(const Vec3I &xyz, int w);

	//从Vec3I构建一个Vec4I
	Vec4I(int x, const Vec3I &yzw);
};

}}
