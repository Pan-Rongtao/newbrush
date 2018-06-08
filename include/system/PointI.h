/*******************************************************
**	PointI
**
**	点（整数形式）
**	
**		包含x，y两个向量的数据结构
**		计算两点之间的距离和曼哈顿长度等
**			为了使用方便，还可直接对x和y向量进行引用操作
**
**		潘荣涛
**	
********************************************************/
#include "core/ValueObject.h"
#include "SystemDef.h"

#pragma once

namespace nb{ namespace System{

class NB_SYSTEM_DECLSPEC_INTERFACE PointI : public Core::ValueObject
{
	NB_OBJECT_TYPE_DECLARE();

//public funs.
public:
	void SetX(int x);
	void SetY(int y);
	void SetXY(int x, int y);

	int GetX() const;
	int GetY() const;
	
	bool IsZero() const;

	bool IsNegative() const;

	//X的引用
	int &X();
	const int &X() const;
	//Y的引用
	int &Y();
	const int &Y() const;

	//返回一个交换X和Y的PointI
	PointI Exchange();


	//两点的直线距离
	int DistanceFrom(const PointI &other) const;
	//两点的曼哈顿距离（两点形成的直角坐标的直角边之和）
	int ManHattanLength(const PointI &other) const;

	bool Equals(const PointI &p) const;

	//做乘法并以返回舍入到最接近的整数值构成的PointI
	PointI MultiplyRound(float f) const;

	//做乘法并以返回舍入到最接近的整数值构成的PointI
	PointI DivideRound(float f) const;

//Constructors & operators override.
public:
	PointI();
	PointI(int x, int y);
	PointI(const PointI &other);
	~PointI();

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

//public static funs.
public:
	static PointI Zero();

private:
	int		m_nX;
	int		m_nY;
};

//gloable inline funs.
static bool Equals(const PointI &p1, const PointI &p2)
{
	return p1.Equals(p2);
}

}}
