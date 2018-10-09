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
#include "Vec3.h"

namespace nb{ namespace core {

class NB_API Matrix3x3
{
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
	Matrix3x3(float *data, uint32_t count);

	//构建一个3x3单位矩阵
	static Matrix3x3 identity();

	//从other构建一个Matrix3x3
	Matrix3x3(const Matrix3x3 &other);

	void operator =(const Matrix3x3 &other);
	bool operator == (const Matrix3x3 &other) const;
	bool operator != (const Matrix3x3 &other) const;
	Vec3 & operator[] (uint32_t row);
	const Vec3 & operator[] (uint32_t row) const;
	Matrix3x3 operator + (float f) const;
	Matrix3x3 operator + (const Matrix3x3 &other) const;
	Matrix3x3 operator - (float f) const;
	Matrix3x3 operator - (const Matrix3x3 &other) const;
	Matrix3x3 operator * (float f) const;
	Matrix3x3 operator * (const Matrix3x3 &right) const;
	Matrix3x3 operator / (float f) const;

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

	//第row行第col列元素
	float &at(uint32_t row, uint32_t col);
	const float &at(uint32_t row, uint32_t col) const;

	//是否是单位矩阵
	bool isIdentity() const;

	//转换为单位矩阵
	void toIdentity();
	/*
	//移动
	void translate(float x, float y);
	void translateX(float x);
	void translateY(float y);

	//旋转角度
	void rotateRadian(float radian, float x, float y);
	void rotateRadianX(float radian);
	void rotateRadianY(float radian);

	//旋转弧度
	void rotateAngle(float angle, float x, float y);
	void rotateAngleX(float angle);
	void rotateAngleY(float angle);

	//缩放
	void scale(float x, float y);
	void scaleX(float x);
	void scaleY(float y);
	*/
private:
	Vec3	m_d[3];
};

}}
