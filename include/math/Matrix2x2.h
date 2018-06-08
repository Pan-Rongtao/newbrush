/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Matrix2x2
				
				描述2 x 2的矩阵数据结构

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/Matrix.h"
#include "math/Vec2.h"

namespace nb{ namespace Math{

class NB_EXPORT Matrix2x2 : public Matrix
{
public:
	//转换为单位矩阵
	void ToIdentity();

public:
	//构建一个Matrix2x2，它的数据是
	//[0.0, 0.0]
	//[0.0, 0.0]
	Matrix2x2();

	//构建一个Matrix2x2，它的数据被初始化
	Matrix2x2(float m0n0, float m0n1, float m1n0, float m1n1);

	//构建一个Matrix2x2，使用Vec2来初始化
	Matrix2x2(const Vec2 &m0, const Vec2 &m1);

	//构建一个Matrix2x2，使用float数组来初始化
	explicit Matrix2x2(float *data);

	//构建一个Matrix2x2，使用float数组的count个元素来初始化
	Matrix2x2(float *data, int count);

public:
	Matrix2x2 operator + (float f) const;
	Matrix2x2 operator + (const Matrix2x2 &other) const;
	Matrix2x2 operator - (float f) const;
	Matrix2x2 operator - (const Matrix2x2 &other) const;
	Matrix2x2 operator * (float f) const;
	Matrix2x2 operator * (const Matrix &right) const;

public:
	//构建一个2x2单位矩阵
	static Matrix2x2 Identity();
};


}}
