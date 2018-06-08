/*******************************************************
**	Point3DII
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
#include "PointI.h"

namespace nb{ namespace System{

class NB_EXPORT Point3DI
{
	//public funs.
public:
	void SetX(int x);
	void SetY(int y);
	void SetZ(int z);
	void SetDepth(int zDepth);
	void SetXY(int x, int y);
	void SetPoint(const PointI &p);
	void SetXYZ(int x, int y, int z);

	int GetX() const;
	int GetY() const;
	int GetZ() const;
	int GetDepth() const;
	PointI GetPoint() const;

	int &X();
	const int &X() const;
	int &Y();
	const int &Y() const;
	int &Z();
	const int &Z() const;

	//获取与另一个三维坐标的距离
	int DistanceFrom(const Point3DI &other) const;

	//是否与other相等，与operator =是等效的
	bool Equals(const Point3DI &other) const;

	//做乘法并以返回舍入到最接近的整数值构成的Point3DI
	Point3DI MultiplyRound(float f) const;

	//做乘法并以返回舍入到最接近的整数值构成的Point3DI
	Point3DI DivideRound(float f) const;

	bool IsZero() const;

	//Constructors & operators override.
public:
	Point3DI();
	Point3DI(const Point3DI &other);
	Point3DI(const PointI &p, int zDepth);
	Point3DI(int x, int y, int z);
	~Point3DI();

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

//public static funs,
public:
	//零值，x=0.0; y=0.0; z=0.0
	static Point3DI Zero();


private:
	int		m_nX;
	int		m_nY;
	int		m_nZ;
};
//Global static funs.
static bool Equals(const Point3DI &left, const Point3DI &right)
{
	return left.Equals(right);
}

}}
