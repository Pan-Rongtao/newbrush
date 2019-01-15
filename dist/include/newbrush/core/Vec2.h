/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec2
				
				描述维度为2的浮点型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace core{

//class Vec2
class NB_API Vec2
{
public:
	//构建一个Vec2对象, 它的分量为（0.0, 0.0)
	Vec2();

	//从其他向量构建一个Vec2，它的分量为(x, y)
	Vec2(float x, float y);

	Vec2(const Vec2 &other);
	~Vec2();

	void operator = (const Vec2 &other);
	bool operator == (const Vec2 &other) const;
	bool operator != (const Vec2 &other) const;
	float & operator [] (uint32_t index);
	const float & operator [] (uint32_t index) const;
	Vec2 operator + (float f) const;
	Vec2 operator + (const Vec2 &v) const;
	Vec2 operator - (float f) const;
	Vec2 operator - (const Vec2 &v) const;
	Vec2 operator * (float f) const;
	Vec2 operator / (float f) const;
	void operator += (float f);
	void operator += (const Vec2 &other);
	void operator -= (float f);
	void operator -= (const Vec2 &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec2 operator - () const;

public:
	//数据
	float *data();
	const float *data() const;

	//维度
	uint32_t dimension() const;

	//返回x分量
	float &x();
	const float &x() const;

	//返回y分量
	float &y();
	const float &y() const;

	//返回下标为index的数
	float &at(uint32_t index);
	const float &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float length() const;

	//标准化
	Vec2 normalized() const;

	//叉乘（向量积）
	Vec2 crossProduct(const Vec2 &other) const;

private:
	float	m_d[2];
};

//class Vec2I
class NB_API Vec2I
{
public:
	//构建一个Vec2I对象, 它的坐标为（0.0, 0.0)
	Vec2I();

	//从其他向量构建一个Vec2I，它的坐标为(x, y)
	Vec2I(int x, int y);

	Vec2I(const Vec2I &other);
	~Vec2I();

	void operator = (const Vec2I &other);
	bool operator == (const Vec2I &other) const;
	bool operator != (const Vec2I &other) const;
	int & operator [] (uint32_t index);
	const int & operator [] (uint32_t index) const;
	Vec2I operator + (int n) const;
	Vec2I operator + (const Vec2I &v) const;
	Vec2I operator - (int n) const;
	Vec2I operator - (const Vec2I &v) const;
	Vec2I operator * (int n) const;
	Vec2I operator / (int n) const;
	void operator += (int n);
	void operator += (const Vec2I &other);
	void operator -= (int n);
	void operator -= (const Vec2I &other);
	void operator *= (int n);
	void operator /= (int n);

	Vec2I operator - () const;

public:
	//数据
	int *data();
	const int *data() const;

	//维度
	uint32_t dimension() const;

	//返回x分量的引用
	int &x();
	const int &x() const;

	//返回y分量的引用
	int &y();
	const int &y() const;

	//返回下标为index的值
	int &at(uint32_t index);
	const int &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float lenght() const;

	Vec2I normalized() const;

	//叉乘（向量积）
	Vec2I crossProduct(const Vec2I &other) const;

private:
	int		m_d[2];
};


//class Vec2B
class NB_API Vec2B
{
public:
	//构建一个Vec2B对象, 它的分量为（false, false)
	Vec2B();

	//从其他向量构建一个Vec2B，它的分量为(x, y)
	Vec2B(bool x, bool y);

	Vec2B(const Vec2B &other);
	~Vec2B();

	void operator = (const Vec2B &other);
	bool operator == (const Vec2B &other) const;
	bool operator != (const Vec2B &other) const;
	bool & operator [] (uint32_t index);
	const bool & operator [] (uint32_t index) const;

public:
	//数据
	bool *data();
	const bool *data() const;

	//维度
	uint32_t dimension() const;

	//返回x分量的引用
	bool &x();
	const bool &x() const;

	//返回y分量的引用
	bool &y();
	const bool &y() const;

	//返回下标为index的值
	bool &at(uint32_t index);
	const bool &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float lenght() const;

	Vec2B crossProduct(const Vec2B &other) const;

private:
	bool	m_d[2];
};


}}
