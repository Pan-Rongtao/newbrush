#include "system/System.h"
#include "system/Point.h"

using namespace nb::System;
using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(Point, ValueObject, &ValueObject::IsEqualFun<Point>, &ValueObject::CopyFun<Point>);

//use Real when define
Point::Point()
{
	SetXY(0.0, 0.0);
}

Point::Point(const Point &other)
{
	SetXY(other.GetX(), other.GetY());
}

Point::Point(float x, float y)
{
	SetXY(x, y);
}

Point::~Point()
{

}

void Point::operator = (const Point &p)
{
	SetXY(p.GetX(), p.GetY());
}

bool Point::operator == (const Point &p) const
{
	return GetX() == p.GetX() && GetY() == p.GetY();
}

bool Point::operator != (const Point &p) const
{
	return !(*this == p);
}

Point Point::operator + (const Point &p) const
{
	return Point(GetX() + p.GetX(), GetY() + p.GetY());
}

Point Point::operator + (float f) const
{
	return Point(GetX() + f, GetY() + f);
}

Point Point::operator - (const Point &p) const
{
	return Point(GetX() - p.GetX(), GetY() - p.GetY());
}

Point Point::operator - (float f) const
{
	return Point(GetX() - f, GetY() - f);
}

Point Point::operator * (float f) const
{
	return Point(GetX() * f, GetY() * f);
}

Point Point::operator / (float f) const
{
	return Point(GetX() / f, GetY() / f);
}

void Point::operator += (const Point &p)
{
	*this = (operator +(p));
}

void Point::operator += (float f)
{
	*this = (operator +(f));
}

void Point::operator -= (const Point &p)
{
	*this = (operator -(p));
}

void Point::operator -= (float f)
{
	*this = (operator -(f));
}

void Point::operator *= (float f)
{
	*this = (operator *(f));
}

void Point::operator /= (float f)
{
	*this = (operator /(f));
}

void Point::SetX(float x)
{
	m_fX = x;
}

void Point::SetY(float y)
{
	m_fY = y;
}

void Point::SetXY(float x, float y)
{
	SetX(x);
	SetY(y);
}

float Point::GetX() const
{
	return m_fX;
}

float Point::GetY() const
{
	return m_fY;
}

bool Point::IsZero() const
{
	return *this == Zero();
}

bool Point::IsNegative() const
{
	return GetX() < 0.0f && GetY() < 0.0f;
}

float &Point::X()
{
	return m_fX;
}

const float &Point::X() const
{
	return m_fX;
}

float &Point::Y()
{
	return m_fY;
}

const float &Point::Y() const
{
	return m_fY;
}

Point Point::Exchange()
{
	return Point(GetY(), GetX());
}

float Point::DistanceFrom(const Point &other) const
{
	return (float)nb::System::Sqrt(nb::System::Pow(GetX() - other.GetX(), 2) + nb::System::Pow(GetY() - other.GetY(), 2));
}

float Point::ManHattanLength(const Point &other) const
{
	return nb::System::Abs(GetX() - other.GetX()) + nb::System::Abs(GetY() - other.GetY());
}

PointI Point::ToPointI() const
{
	return PointI((int)GetX(), (int)GetY());
}

PointI Point::ToRoundPointI() const
{
	return PointI(nb::System::Round(GetX()), nb::System::Round(GetY()));
}

bool Point::Equals(const Point &p) const
{
	return *this == p;
}

Point Point::Zero()
{
	return Point(0.0, 0.0);
}

Point Point::FromPointI(const PointI &p)
{
	return Point((float)(p.GetX()), (float)(p.GetY()));
}
