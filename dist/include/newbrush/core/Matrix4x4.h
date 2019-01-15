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
#include "Vec4.h"

namespace nb{ namespace core {

class NB_API Matrix4x4
{
public:
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
	Matrix4x4(float *data, uint32_t count);

	//单位Matrix4x4
	static Matrix4x4 identity();

	//平移矩阵
	static Matrix4x4 translateMatrix(float x, float y, float z);

	//缩放矩阵
	static Matrix4x4 scaleMatrix(float scaleX, float scaleY, float scaleZ);

	//从other构建一个Matrix2x2
	Matrix4x4(const Matrix4x4 &other);

	void operator = (const Matrix4x4 &other);
	bool operator == (const Matrix4x4 &other) const;
	bool operator != (const Matrix4x4 &other) const;
	Vec4 & operator[] (uint32_t row);
	const Vec4 & operator[] (uint32_t row) const;
	Matrix4x4 operator + (float f) const;
	Matrix4x4 operator + (const Matrix4x4 &other) const;
	Matrix4x4 operator - (float f) const;
	Matrix4x4 operator - (const Matrix4x4 &other) const;
	Matrix4x4 operator * (float f) const;
	Matrix4x4 operator * (const Matrix4x4 &right) const;
	Matrix4x4 operator / (float f) const;

public:
	//数据
	float *data();
	const float *data() const;

	//元素个数
	uint32_t size() const;

	//行数
	uint32_t row() const;

	//列数
	uint32_t column() const;

	//下标为row, col的数据
	float &at(uint32_t row, uint32_t col);
	const float &at(uint32_t row, uint32_t col) const;

	//是否是单位矩阵
	bool isIdentity() const;

	//转换为单位矩阵
	void toIdentity();

	//移动
	Matrix4x4 &translate(float x, float y, float z);
	Matrix4x4 &translateX(float x);
	Matrix4x4 &translateY(float y);
	Matrix4x4 &translateZ(float z);

	//旋转角度
	Matrix4x4 &rotateRadian(float radian, float x, float y, float z);
	Matrix4x4 &rotateRadianX(float radian);
	Matrix4x4 &rotateRadianY(float radian);
	Matrix4x4 &rotateRadianZ(float radian);

	//旋转弧度
	Matrix4x4 &rotateAngle(float angle, float x, float y, float z);
	Matrix4x4 &rotateAngleX(float angle);
	Matrix4x4 &rotateAngleY(float angle);
	Matrix4x4 &rotateAngleZ(float angle);

	//缩放
	Matrix4x4 &scale(float x, float y, float z);
	Matrix4x4 &scaleX(float x);
	Matrix4x4 &scaleY(float y);
	Matrix4x4 &scaleZ(float z);
	Matrix4x4 &scaleUniform(float uniform);

private:
	Vec4	m_d[4];
};

}}
