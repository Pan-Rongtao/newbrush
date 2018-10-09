/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-02

* 简要描述: Vec4
				
				描述维度为4的浮点型向量

* 修改记录:

*****************************************************************************/
#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace nb{ namespace core{

//class Vec4
class NB_API Vec4
{
public:
	//构建一个Vec4，它的分量为(0.0, 0.0, 0.0, 0.0)
	Vec4();

	//构建一个Vec4，它的分量为(x, y, z, w);
	Vec4(float x, float y, float z, float w);

	//从Vec2构建一个Vec4
	Vec4(const Vec2 &xy, const Vec2 &zw);

	//从Vec2构建一个Vec4
	Vec4(float x, const Vec2 &yz, float w);

	//从Vec2构建一个Vec4
	Vec4(float x, float y, const Vec2 &zw);

	//从Vec3构建一个Vec4
	Vec4(const Vec3 &xyz, float w);

	//从Vec3构建一个Vec4
	Vec4(float x, const Vec3 &yzw);

	Vec4(const Vec4 &other);

	void operator = (const Vec4 &other);
	bool operator == (const Vec4 &other) const;
	bool operator != (const Vec4 &other) const;
	float & operator [] (uint32_t index);
	const float & operator [] (uint32_t index) const;
	Vec4 operator + (float f) const;
	Vec4 operator + (const Vec4 &v) const;
	Vec4 operator - (float f) const;
	Vec4 operator - (const Vec4 &v) const;
	Vec4 operator * (float f) const;
	Vec4 operator / (float f) const;
	void operator += (float f);
	void operator += (const Vec4 &other);
	void operator -= (float f);
	void operator -= (const Vec4 &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec4 operator - () const;

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

	//返回w分量的引用
	float &w();
	const float &w() const;

	//返回xy分量
	Vec2 xy() const;

	//返回yz分量
	Vec2 yz() const;

	//返回zw分量
	Vec2 zw() const;

	//返回xyz分量
	Vec3 xyz() const;

	//返回yzw分量
	Vec3 yzw() const;

	//返回下标为index的数
	float &at(uint32_t index);
	const float &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float length() const;

	//标准化
	Vec4 normalized() const;

private:
	float	m_d[4];
};

//class Vec4I
class NB_API Vec4I
{
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

	Vec4I(const Vec4I &other);

	void operator = (const Vec4I &other);
	bool operator == (const Vec4I &other) const;
	bool operator != (const Vec4I &other) const;
	int & operator [] (uint32_t index);
	const int & operator [] (uint32_t index) const;
	Vec4I operator + (int n) const;
	Vec4I operator + (const Vec4I &v) const;
	Vec4I operator - (int n) const;
	Vec4I operator - (const Vec4I &v) const;
	Vec4I operator * (int n) const;
	Vec4I operator / (int n) const;
	void operator += (int n);
	void operator += (const Vec4I &other);
	void operator -= (int n);
	void operator -= (const Vec4I &other);
	void operator *= (int n);
	void operator /= (int n);

	Vec4I operator - () const;

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

	//返回w分量的引用
	int &w();
	const int &w() const;

	//返回xy分量
	Vec2I xy() const;

	//返回yz分量
	Vec2I yz() const;

	//返回zw分量
	Vec2I zw() const;

	//返回xyz分量
	Vec3I xyz() const;

	//返回yzw分量
	Vec3I yzw() const;

	//返回下标为index的值
	int &at(uint32_t index);
	const int &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float lenght() const;

	Vec4I normalized() const;

private:
	int		m_d[4];
};

//class Vec4B
class NB_API Vec4B
{
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

	Vec4B(const Vec4B &other);

	void operator = (const Vec4B &other);
	bool operator == (const Vec4B &other) const;
	bool operator != (const Vec4B &other) const;
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

	//返回w分量的引用
	bool &w();
	const bool &w() const;

	//返回xy分量
	Vec2B xy() const;

	//返回yz分量
	Vec2B yz() const;

	//返回zw分量
	Vec2B zw() const;

	//返回xyz分量
	Vec3B xyz() const;

	//返回yzw分量
	Vec3B yzw() const;

	//返回下标为index的值
	bool &at(uint32_t index);
	const bool &at(uint32_t index) const;

	//模/长度
	float norm() const;
	float lenght() const;

	Vec4B crossProduct(const Vec4B &other) const;

private:
	bool	m_d[4];
};


}}
