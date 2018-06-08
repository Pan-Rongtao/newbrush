/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Matrix4x4
				
				描述4 x 4的矩阵数据结构

* 修改记录:

*****************************************************************************/
#pragma once
#include "math/Matrix.h"
#include "math/Vec4.h"

namespace nb{ namespace Math{

class NB_EXPORT Matrix4x4 : public Matrix
{
public:
	//转换为单位矩阵
	void ToIdentity();

	//移动
	Matrix4x4 Translate(float offsetX, float offsetY, float offsetZ);
	Matrix4x4 TranslateX(float offsetX);
	Matrix4x4 TranslateY(float offsetY);
	Matrix4x4 TranslateZ(float offsetZ);

	//旋转角度
	Matrix4x4 RotateRadian(float radian, float x, float y, float z);
	Matrix4x4 RotateRadianX(float radian);
	Matrix4x4 RotateRadianY(float radian);
	Matrix4x4 RotateRadianZ(float radian);

	//旋转弧度
	Matrix4x4 RotateAngle(float angle, float x, float y, float z);
	Matrix4x4 RotateAngleX(float angle);
	Matrix4x4 RotateAngleY(float angle);
	Matrix4x4 RotateAngleZ(float angle);

	//缩放
	Matrix4x4 Scale(float scaleX, float scaleY, float scaleZ);
	Matrix4x4 ScaleX(float scaleX);
	Matrix4x4 ScaleY(float scaleY);
	Matrix4x4 ScaleZ(float scaleZ);
	Matrix4x4 ScaleUniform(float uniform);

public:
	//构建一个Matrix4x4，它的数据是
	//[0.0, 0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0, 0.0]
	Matrix4x4();

	//构建一个Matrix4x4，它的数据被初始化
	Matrix4x4(float m0n0, float m0n1, float m0n2, float m0n3, float m1n0, float m1n1, float m1n2, float m1n3, float m2n0, float m2n1, float m2n2, float m2n3, float m3n0, float m3n1, float m3n2, float m3n3);

	//构建一个Matrix4x4，使用Vec2来初始化
	Matrix4x4(const Vec4 &m0, const Vec4 &m1, const Vec4 &m2, const Vec4 &m3);

	//构建一个Matrix4x4，使用float数组来初始化
	explicit Matrix4x4(float *data);

	//构建一个Matrix4x4，使用float数组的count个元素来初始化
	Matrix4x4(float *data, int count);

public:
	Matrix4x4 operator + (float f) const;
	Matrix4x4 operator + (const Matrix4x4 &other) const;
	Matrix4x4 operator - (float f) const;
	Matrix4x4 operator - (const Matrix4x4 &other) const;
	Matrix4x4 operator * (float f) const;
	Matrix4x4 operator * (const Matrix4x4 &right) const;

public:
	//单位Matrix4x4
	static Matrix4x4 Identify();

	//平移矩阵
	static Matrix4x4 TranslateMatrix(float offsetX, float offsetY, float offsetZ);

	//缩放矩阵
	static Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ);

	//旋转矩阵
	static Matrix4x4 RotateMatrix();
};

}}
