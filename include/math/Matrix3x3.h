/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Matrix3x3
				
				描述3 x 3的矩阵数据结构

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/Matrix.h"
#include "math/Vec3.h"

namespace nb{ namespace Math{

class NB_EXPORT Matrix3x3 : public Matrix
{
public:
	//转换为单位矩阵
	void ToIdentity();

	//移动
	void Translate(float x, float y);
	void TranslateX(float x);
	void TranslateY(float y);

	//旋转角度
	void RotateRadian(float radian, float x, float y);
	void RotateRadianX(float radian);
	void RotateRadianY(float radian);

	//旋转弧度
	void RotateAngle(float angle, float x, float y);
	void RotateAngleX(float angle);
	void RotateAngleY(float angle);

	//缩放
	void Scale(float x, float y);
	void ScaleX(float x);
	void ScaleY(float y);

public:
	//构建一个Matrix3x3，它的数据是
	//[0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0]
	Matrix3x3();

	//构建一个Matrix3x3，它的数据被初始化
	Matrix3x3(float m0n0, float m0n1, float m0n2, float m1n0, float m1n1, float m1n2, float m2n0, float m2n1, float m2n2);

	//构建一个Matrix3x3，使用Vec2来初始化
	Matrix3x3(const Vec3 &m0, const Vec3 &m1, const Vec3 &m2);

	//构建一个Matrix3x3，使用float数组来初始化
	explicit Matrix3x3(float *data);

	//构建一个Matrix3x3，使用float数组的count个元素来初始化
	Matrix3x3(float *data, int count);

public:
	Matrix3x3 operator + (float f) const;
	Matrix3x3 operator + (const Matrix3x3 &other) const;
	Matrix3x3 operator - (float f) const;
	Matrix3x3 operator - (const Matrix3x3 &other) const;
	Matrix3x3 operator * (float f) const;
	Matrix3x3 operator * (const Matrix &right) const;

public:
	//构建一个3x3单位矩阵
	static Matrix3x3 Identity();
};

}}
