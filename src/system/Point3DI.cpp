#include "system/Point3DI.h"
#include "system/System.h"

using namespace nb::System;
Point3DI::Point3DI()
{
	SetXYZ(0, 0, 0);
}

Point3DI::Point3DI(const Point3DI &other)
{
	SetXYZ(other.GetX(), other.GetY(), other.GetZ());
}

Point3DI::Point3DI(const PointI &p, int zDepth)
{
	SetXYZ(p.GetX(), p.GetY(), zDepth);
}

Point3DI::Point3DI(int x, int y, int z)
{
	SetXYZ(x, y, z);
}

Point3DI::~Point3DI()
{

}

void Point3DI::operator = (const Point3DI &other)
{
	SetXYZ(other.GetX(), other.GetY(), other.GetZ());
}

bool Point3DI::operator == (const Point3DI &other) const
{
	return GetX() == other.GetX() && GetY() == other.GetY() && GetZ() == other.GetZ();
}

bool Point3DI::operator != (const Point3DI &other) const
{
	return !(operator ==(other));
}

void Point3DI::SetX(int x)
{
	m_nX = x;
}

void Point3DI::SetY(int y)
{
	m_nY = y;
}

void Point3DI::SetZ(int z)
{
	m_nZ = z;
}

void Point3DI::SetDepth(int zDepth)
{
	m_nZ = zDepth;
}

void Point3DI::SetXY(int x, int y)
{
	SetX(x);
	SetY(y);
}

void Point3DI::SetPoint(const PointI &p)
{
	SetXY(p.GetX(), p.GetY());
}

void Point3DI::SetXYZ(int x, int y, int z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

int Point3DI::GetX() const
{
	return m_nX;
}

int Point3DI::GetY() const
{
	return m_nY;
}

int Point3DI::GetZ() const
{
	return m_nZ;
}

int Point3DI::GetDepth() const
{
	return GetZ();
}

PointI Point3DI::GetPoint() const
{
	return PointI(GetX(), GetY());
}

int &Point3DI::X()
{
	return m_nX;
}

const int &Point3DI::X() const
{
	return m_nX;
}

int &Point3DI::Y()
{
	return m_nY;
}

const int &Point3DI::Y() const
{
	return m_nY;
}

int &Point3DI::Z()
{
	return m_nZ;
}

const int &Point3DI::Z() const
{
	return m_nZ;
}

bool Point3DI::IsZero() const
{
	return *this == Zero();
}

int Point3DI::DistanceFrom(const Point3DI &other) const
{
	return (int)(nb::System::Sqrt(nb::System::Pow(float(GetX() - other.GetX()), 2) + nb::System::Pow(float(GetY() - other.GetY()), 2) + nb::System::Pow((float)(GetZ() - other.GetZ()), 2)));
}

bool Point3DI::Equals(const Point3DI &other) const
{
	return *this == other;
}

Point3DI Point3DI::MultiplyRound(float f) const
{
	return Point3DI(nb::System::Round(GetX() * f), nb::System::Round(GetY() * f), nb::System::Round(GetZ() * f));
}

Point3DI Point3DI::DivideRound(float f) const
{
	return Point3DI(nb::System::Round(GetX() / f), nb::System::Round(GetY() / f), nb::System::Round(GetZ() / f));
}

Point3DI Point3DI::operator + (const Point3DI &other) const
{
	return Point3DI(GetX() + other.GetX(), GetY() + other.GetY(), GetZ() + other.GetZ());
}

Point3DI Point3DI::operator + (int n) const
{
	return Point3DI(GetX() + n, GetY() + n, GetZ() + n);
}

Point3DI Point3DI::operator - (const Point3DI &other) const
{
	return Point3DI(GetX() - other.GetX(), GetY() - other.GetY(), GetZ() - other.GetZ());
}

Point3DI Point3DI::operator - (int n) const
{
	return Point3DI(GetX() - n, GetY() - n, GetZ() - n);
}

Point3DI Point3DI::operator * (int n) const
{
	return Point3DI(GetX() * n, GetY() * n, GetZ() * n);
}

Point3DI Point3DI::operator * (float f) const
{
	return Point3DI((int)(GetX() * f), (int)(GetY() * f), (int)(GetZ() * f));
}
//除以0的异常
Point3DI Point3DI::operator / (int n) const
{
	return Point3DI(GetX() / n, GetY() / n, GetZ() / n);
}

Point3DI Point3DI::operator / (float f) const
{
	return Point3DI((int)(GetX() / f), (int)(GetY() / f), (int)(GetZ() / f));
}

void Point3DI::operator += (const Point3DI &other)
{
	return *this = (operator + (other));
}

void Point3DI::operator += (int n)
{
	return *this = (operator + (n));
}

void Point3DI::operator -= (const Point3DI &other)
{
	return *this = (operator - (other));
}

void Point3DI::operator -= (int n)
{
	return *this = (operator - (n));
}

void Point3DI::operator *= (int n)
{
	return *this = (operator * (n));
}

void Point3DI::operator *= (float f)
{
	return *this = (operator * (f));
}

void Point3DI::operator /= (int n)
{
	return *this = (operator / (n));
}

void Point3DI::operator /= (float f)
{
	return *this = (operator / (f));
}

Point3DI Point3DI::Zero()
{
	return Point3DI(0, 0, 0);
}
