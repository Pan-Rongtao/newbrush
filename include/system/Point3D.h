/*******************************************************
**	Point3D
**
**	三维坐标（浮点形式）
**	
**		包含x，y，z三个向量的数据结构
**		计算两个坐标之间的距离等
**			为了使用方便，还可直接对x、y、z向量进行引用操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Point.h"
#include "Point3DI.h"

namespace nb{ namespace System{

class NB_EXPORT Point3D
{
//public funs.
public:
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetDepth(float zDepth);
	void SetXY(float x, float y);
	void SetPoint(const Point &p);
	void SetXYZ(float x, float y, float z);

	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetDepth() const;
	Point GetPoint() const;

	float &X();
	const float &X() const;
	float &Y();
	const float &Y() const;
	float &Z();
	const float &Z() const;

	//获取与另一个三维坐标的距离
	float DistanceFrom(const Point3D &other) const;

	//转换成Point3DI
	Point3DI ToPoint3DI() const;

	//舍入到最接近的整数值构成的Point3DI
	Point3DI ToRoundPoint3DI() const;

	//是否与other相等，与operator =是等效的
	bool Equals(const Point3D &other) const;

	bool IsZero() const;
//Constructors & operators override.
public:
	Point3D();
	Point3D(const Point3D &other);
	Point3D(float x, float y, float z);
	Point3D(const Point &p, float zDepth);
	~Point3D();

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

//public static funs,
public:
	//零值，x=0.0; y=0.0; z=0.0
	static Point3D Zero();

	//从Point3DI实例构建一个Point3D
	static Point3D FromPoint3DI(const Point3DI &p);

private:
	float	m_fX;
	float	m_fY;
	float	m_fZ;
};

static bool Equals(const Point3D &left, const Point3D &right)
{
	return left.Equals(right);
}

}}
