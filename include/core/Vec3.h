/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec3
				
				描述维度为3的浮点型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "Vec2.h"

namespace nb{ namespace core{

//class Vec3
class NB_API Vec3
{
public:
	//构建一个Vec3，它的分量为(0.0, 0.0, 0.0)
	Vec3();

	//构建一个Vec3，它的坐标为(x, y, z)
	Vec3(float x, float y, float z);

	//从一个Vec2构建一个Vec3
	Vec3(const Vec2 &xy, float z);

	//从一个Vec2构建一个
	Vec3(float x, const Vec2 &yz);

	Vec3(const Vec3 &other);

	void operator = (const Vec3 &other);
	bool operator == (const Vec3 &other) const;
	bool operator != (const Vec3 &other) const;
	float & operator [] (uint32_t index);
	const float & operator [] (uint32_t index) const;
	Vec3 operator + (float f) const;
	Vec3 operator + (const Vec3 &v) const;
	Vec3 operator - (float f) const;
	Vec3 operator - (const Vec3 &v) const;
	Vec3 operator * (float f) const;
	Vec3 operator / (float f) const;
	void operator += (float f);
	void operator += (const Vec3 &other);
	void operator -= (float f);
	void operator -= (const Vec3 &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec3 operator - () const;

public:
	//数据
	float *data();
	const float *data() const;

	//维度
	uint32_t dimension() const;

	//返回x分量的引用
	float &x();
	const float &x() const;

	//返回y分量的引用
	float &y();
	const float &y() const;

	//返回z分量的引用
	float &z();
	const float &z() const;

	//返回xy分量
	Vec2 xy() const;

	//返回yz分量
	Vec2 yz() const;

	//返回下标为index的数
	float &at(uint32_t index);
	const float &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float length() const;

	//标准化
	Vec3 normalized() const;

	//点乘（数量积）
	float dotProduct(const Vec3 &other) const;

	//叉乘（向量积）
	Vec3 crossProduct(const Vec3 &other) const;

private:
	float	m_d[3];
};

//class Vec3I
class NB_API Vec3I
{
public:
	//构建一个Vec3I，它的坐标为(0.0, 0.0, 0.0)
	Vec3I();

	//构建一个Vec3I，它的坐标为(x, y, z)
	Vec3I(int x, int y, int z);

	//从一个Vec2I构建一个Vec3I
	Vec3I(const Vec2I &xy, int z);

	//从一个Vec2I构建一个
	Vec3I(int x, const Vec2I &yz);

	Vec3I(const Vec3I &other);

	void operator = (const Vec3I &other);
	bool operator == (const Vec3I &other) const;
	bool operator != (const Vec3I &other) const;
	int & operator [] (uint32_t index);
	const int & operator [] (uint32_t index) const;
	Vec3I operator + (int n) const;
	Vec3I operator + (const Vec3I &v) const;
	Vec3I operator - (int n) const;
	Vec3I operator - (const Vec3I &v) const;
	Vec3I operator * (int n) const;
	Vec3I operator / (int n) const;
	void operator += (int n);
	void operator += (const Vec3I &other);
	void operator -= (int n);
	void operator -= (const Vec3I &other);
	void operator *= (int n);
	void operator /= (int n);

	Vec3I operator - () const;


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

	//返回z分量的引用
	int &z();
	const int &z() const;

	//返回xy分量
	Vec2I xy() const;

	//返回yz分量
	Vec2I yz() const;

	//返回下标为index的值
	int &at(uint32_t index);
	const int &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float lenght() const;

	Vec3I normalized() const;

	//叉乘（向量积）
	Vec3I crossProduct(const Vec3I &other) const;

private:
	int		m_d[3];
};

//class Vec3B
class NB_API Vec3B
{
public:
	//构建一个Vec3B，它的坐标为(0.0, 0.0, 0.0)
	Vec3B();

	//构建一个Vec3B，它的坐标为(x, y, z)
	Vec3B(bool x, bool y, bool z);

	//从一个Vec2B构建一个Vec3B
	Vec3B(const Vec2B &xy, bool z);

	//从一个Vec2B构建一个
	Vec3B(bool x, const Vec2B &yz);

	Vec3B(const Vec3B &other);

	void operator = (const Vec3B &other);
	bool operator == (const Vec3B &other) const;
	bool operator != (const Vec3B &other) const;
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

	//返回z分量的引用
	bool &z();
	const bool &z() const;

	//返回xy分量
	Vec2B xy() const;

	//返回yz分量
	Vec2B yz() const;

	//返回下标为index的值
	bool &at(uint32_t index);
	const bool &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float lenght() const;

	Vec3B crossProduct(const Vec3B &other) const;

private:
	bool	m_d[3];
};


static nb::core::Vec3 operator * (float f, nb::core::Vec3 v)
{
	return v * f;
}

}}
