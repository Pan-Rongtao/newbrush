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
#include "../core/Def.h"

namespace nb{ namespace core {

//class Point
class NB_API Point
{
public:
	Point();
	Point(float x, float y);
	Point(const Point &other);
	~Point();
	//零值，x=0.0; y=0.0
	static Point zero();

	void operator = (const Point &p);
	bool operator == (const Point &p) const;
	bool operator != (const Point &p) const;
	Point operator + (const Point &p) const;
	Point operator + (float f) const;
	Point operator - (const Point &p) const;
	Point operator - (float f) const;
	Point operator * (float f) const;
	Point operator / (float f) const;
	void operator += (const Point &p);
	void operator += (float f);
	void operator -= (const Point &p);
	void operator -= (float f);
	void operator *= (float f);
	void operator /= (float f);

public:
	//设置x的值
	void setX(float x);

	//设置y的值
	void setY(float y);

	//设置x，y的值
	void reset(float x, float y);

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

	//交换x，y
	Point &swap();

	//两点的直线距离
	float distance(const Point &other) const;

	//两点的曼哈顿距离（两点形成的直角坐标的直角边之和）
	float manhattanLength(const Point &other) const;

	//是否与p相等，与operator =是等效的
	bool equals(const Point &p) const;

private:
	float		m_x;
	float		m_y;
};

//class PointI
class NB_API PointI
{
public:
	PointI();
	PointI(int x, int y);
	PointI(const PointI &other);
	~PointI();
	static PointI zero();

	void operator = (const PointI &p);
	bool operator == (const PointI &p) const;
	bool operator != (const PointI &p) const;
	PointI operator + (const PointI &p) const;
	PointI operator + (int n) const;
	PointI operator - (const PointI &p) const;
	PointI operator - (int n) const;
	PointI operator * (int n) const;
	PointI operator * (float f) const;
	PointI operator / (int n) const;
	PointI operator / (float f) const;
	void operator += (const PointI &p);
	void operator += (int n);
	void operator -= (const PointI &p);
	void operator -= (int n);
	void operator *= (int n);
	void operator *= (float f);
	void operator /= (int n);
	void operator /= (float f);

public:
	void setX(int x);
	void setY(int y);
	void reset(int x, int y);

	//x
	int &x();
	const int &x() const;

	//y
	int &y();
	const int &y() const;

	//是否是(0, 0)
	bool isZero() const;

	//是否是负值
	bool isNegative() const;

	//交换x, y
	PointI &swap();

	//两点的直线距离
	int distance(const PointI &other) const;

	//两点的曼哈顿距离（两点形成的直角坐标的直角边之和）
	int manhattanLength(const PointI &other) const;

	//是否相等
	bool equals(const PointI &p) const;

	//做乘法并以返回舍入到最接近的整数值构成的PointI
	PointI multiplyRound(float f) const;

	//做乘法并以返回舍入到最接近的整数值构成的PointI
	PointI divideRound(float f) const;

private:
	int		m_x;
	int		m_y;
};

//////////class Point3D
class NB_API Point3D
{
public:
	Point3D();
	Point3D(const Point3D &other);
	Point3D(float x, float y, float z);
	Point3D(const Point &p, float z);
	~Point3D();
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
	void setX(float x);

	//设置y
	void setY(float y);

	//设置z
	void setZ(float z);

	//设置xy
	void setXY(float x, float y);

	//重置
	void reset(float x, float y, float z);

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

	//是否与other相等，与operator =是等效的
	bool equals(const Point3D &other) const;

	//是否是(0.0, 0.0, 0.0)
	bool isZero() const;

private:
	float	m_x;
	float	m_y;
	float	m_z;
};

//class Point3DI
class NB_API Point3DI
{
public:
	Point3DI();
	Point3DI(const Point3DI &other);
	Point3DI(const PointI &p, int z);
	Point3DI(int x, int y, int z);
	~Point3DI();
	//零值，x=0.0; y=0.0; z=0.0
	static Point3DI zero();

	void operator = (const Point3DI &other);
	bool operator == (const Point3DI &other) const;
	bool operator != (const Point3DI &other) const;
	Point3DI operator + (const Point3DI &other) const;
	Point3DI operator + (int n) const;
	Point3DI operator - (const Point3DI &other) const;
	Point3DI operator - (int n) const;
	Point3DI operator * (int n) const;
	Point3DI operator * (float f) const;
	Point3DI operator / (int n) const;
	Point3DI operator / (float f) const;
	void operator += (const Point3DI &other);
	void operator += (int n);
	void operator -= (const Point3DI &other);
	void operator -= (int n);
	void operator *= (int n);
	void operator *= (float f);
	void operator /= (int n);
	void operator /= (float f);

public:
	//设置x
	void setX(int x);

	//设置y
	void setY(int y);

	//设置z
	void setZ(int z);

	//设置xy
	void setXY(int x, int y);

	//重置
	void reset(int x, int y, int z);

	//x
	int &x();
	const int &x() const;

	//y
	int &y();
	const int &y() const;

	//z
	int &z();
	const int &z() const;

	//xy
	PointI xy() const;

	//获取与另一个三维坐标的距离
	int distance(const Point3DI &other) const;

	//是否与other相等，与operator =是等效的
	bool equals(const Point3DI &other) const;

	//做乘法并以返回舍入到最接近的整数值构成的Point3DI
	Point3DI multiplyRound(float f) const;

	//做乘法并以返回舍入到最接近的整数值构成的Point3DI
	Point3DI divideRound(float f) const;

	//是否是(0, 0, 0)
	bool isZero() const;

private:
	int		m_x;
	int		m_y;
	int		m_z;
};


static bool equals(const Point &p0, const Point &p1)
{
	return p0.equals(p1);
}

static bool equals(const PointI &p0, const PointI &p1)
{
	return p0.equals(p1);
}

static bool equals(const Point3D &p0, const Point3D &p1)
{
	return p0.equals(p1);
}

static bool Equals(const Point3DI &p0, const Point3DI &p1)
{
	return p0.equals(p1);
}

}}
