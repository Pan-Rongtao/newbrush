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
#include "Vec2.h"

namespace nb{ namespace core{

class NB_API Matrix2x2
{
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
	Matrix2x2(float *data, uint32_t count);

	//构建一个2x2单位矩阵
	static Matrix2x2 identity();

	//从other构建一个Matrix2x2
	Matrix2x2(const Matrix2x2 &other);

	void operator =(const Matrix2x2 &other);
	bool operator == (const Matrix2x2 &other) const;
	bool operator != (const Matrix2x2 &other) const;
	Vec2 & operator[] (uint32_t row);
	const Vec2 & operator[] (uint32_t row) const;
	Matrix2x2 operator + (float f) const;
	Matrix2x2 operator + (const Matrix2x2 &other) const;
	Matrix2x2 operator - (float f) const;
	Matrix2x2 operator - (const Matrix2x2 &other) const;
	Matrix2x2 operator * (float f) const;
	Matrix2x2 operator * (const Matrix2x2 &right) const;
	Matrix2x2 operator / (float f) const;

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

private:
	Vec2	m_d[2];
};

}}
