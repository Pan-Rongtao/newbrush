/*******************************************************
**	Point
**
**	点（浮点形式）
**	
**		包含x，y两个向量的数据结构
**		计算两点之间的距离和曼哈顿长度等
**			为了使用方便，还可直接对x和y向量进行引用操作
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "PointI.h"

//use Real when define
namespace nb{ namespace System{

class NB_EXPORT Point : public Core::ValueObject
{
	NB_OBJECT_TYPE_DECLARE();

//public funs.
public:
	//设置x的值
	void SetX(float x);

	//设置y的值
	void SetY(float y);

	//设置x，y的值
	void SetXY(float x, float y);

	//获取x的值
	float GetX() const;

	//获取y的值
	float GetY() const;

	//判读是否是零值
	bool IsZero() const;

	//是否是负值
	bool IsNegative() const;

	//X的引用
	float &X();
	const float &X() const;

	//Y的引用
	float &Y();
	const float &Y() const;


	//返回一个交换的X和Y的Point
	Point Exchange();

	//两点的直线距离
	float DistanceFrom(const Point &other) const;
	//两点的曼哈顿距离（两点形成的直角坐标的直角边之和）
	float ManHattanLength(const Point &other) const;

	//转换成PointI
	PointI ToPointI() const;

	//舍入到最接近的整数值构成的PointI
	PointI ToRoundPointI() const;

	//是否与p相等，与operator =是等效的
	bool Equals(const Point &p) const;

	//Constructors & operators override.
public:
	Point();
	Point(float x, float y);
	Point(const Point &other);
	~Point();

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

	//public static funs.
public:
	//零值，x=0.0; y=0.0
	static Point Zero();

	//从PointI实例构建一个Point
	static Point FromPointI(const PointI &p);

private:
	float		m_fX;
	float		m_fY;
};

//gloable inline funs.
static bool Equals(const Point &p1, const Point &p2)
{
	return p1.Equals(p2);
}

}}
