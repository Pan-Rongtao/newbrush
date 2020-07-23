/*******************************************************
**	Point/PointI/Point3D/Point3DI
**
**	点
**	
**		包含x，y两个向量的数据结构
**		计算两点之间的距离和曼哈顿长度等
**			为了使用方便，还可直接对x和y向量进行引用操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/core/Def.h"

namespace nb{

//class Point
class NB_API Point
{
public:
	//构建一个Point(0.0, 0.0)
	Point();

	//构建一个Point(x, y)
	Point(float x, float y);

	//从其他Point构建一个新的Point
	Point(const Point &other);

	//零值，x=0.0; y=0.0
	static Point zero();

	void operator = (const Point &p) &;
	bool operator == (const Point &p) const;
	bool operator != (const Point &p) const;
	Point operator + (const Point &p) const;
	Point operator + (float f) const;
	Point operator - (const Point &p) const;
	Point operator - (float f) const;
	Point operator * (float f) const;
	Point operator / (float f) const;
	void operator += (const Point &p) &;
	void operator += (float f) &;
	void operator -= (const Point &p) &;
	void operator -= (float f) &;
	void operator *= (float f) &;
	void operator /= (float f) &;

public:
	//设置x的值
	void setX(float x) &;

	//设置y的值
	void setY(float y) &;

	//设置x，y的值
	void reset(float x, float y) &;

	//X的引用
	float &x();
	const float &x() const;

	//Y的引用
	float &y();
	const float &y() const;

	//判读是否是零值
	bool isZero() const;

	//是否是负值
	bool isNegative() const;

	//两点的直线距离
	float distance(const Point &other) const;

	//两点的曼哈顿距离（两点形成的直角坐标的直角边之和）
	float manhattanLength(const Point &other) const;

private:
	float		m_x;
	float		m_y;
};

//////////class Point3D
class NB_API Point3D
{
public:
	//构建一个Point3D(0.0, 0.0, 0.0)
	Point3D();

	//构建一个Point3D(x, y, z)
	Point3D(float x, float y, float z);

	//构建一个Point3D(p.x, p.y, z)
	Point3D(const Point &p, float z);

	//从其他Piont3D构建一个新的Point3D
	Point3D(const Point3D &other);

	//零值，x=0.0; y=0.0; z=0.0
	static Point3D zero();

	void operator = (const Point3D &other);
	bool operator == (const Point3D &other) const;
	bool operator != (const Point3D &other) const;
	Point3D operator + (const Point3D &other) const;
	Point3D operator + (float f) const;
	Point3D operator - (const Point3D &other) const;
	Point3D operator - (float f) const;
	Point3D operator * (float f) const;
	Point3D operator / (float f) const;
	void operator += (const Point3D &other);
	void operator += (float f);
	void operator -= (const Point3D &other);
	void operator -= (float f);
	void operator *= (float f);
	void operator /= (float f);

public:
	//设置x
	void setX(float x) &;

	//设置y
	void setY(float y) &;

	//设置z
	void setZ(float z) &;

	//设置xy
	void setXY(float x, float y) &;

	//重置
	void reset(float x, float y, float z) &;

	//x
	float &x();
	const float &x() const;

	//y
	float &y();
	const float &y() const;

	//z
	float &z();
	const float &z() const;

	//xy
	Point xy() const;

	//获取与另一个三维坐标的距离
	float distance(const Point3D &other) const;

	//是否是(0.0, 0.0, 0.0)
	bool isZero() const;

private:
	float	m_x;
	float	m_y;
	float	m_z;
};

}
