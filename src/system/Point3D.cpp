#include "system/Point3D.h"
#include "system/System.h"

using namespace nb::System;
Point3D::Point3D()
{
	SetXYZ(0.0f, 0.0f, 0.0f);
}

Point3D::Point3D(const Point3D &other)
{
	SetXYZ(other.GetX(), other.GetY(), other.GetZ());
}

Point3D::Point3D(float x, float y, float z)
{
	SetXYZ(x, y, z);
}

Point3D::Point3D(const Point &p, float zDepth)
{
	SetXYZ(p.GetX(), p.GetY(), zDepth);
}

Point3D::~Point3D()
{

}

void Point3D::operator = (const Point3D &other)
{
	SetXYZ(other.GetX(), other.GetY(), other.GetZ());
}

void Point3D::SetX(float x)
{
	m_fX = x;
}

void Point3D::SetY(float y)
{
	m_fY = y;
}

void Point3D::SetZ(float z)
{
	m_fZ = z;
}

void Point3D::SetDepth(float zDepth)
{
	SetZ(zDepth);
}

void Point3D::SetXY(float x, float y)
{
	SetX(x);
	SetY(y);
}

void Point3D::SetPoint(const Point &p)
{
	SetXY(p.GetX(), p.GetY());
}

void Point3D::SetXYZ(float x, float y, float z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

float Point3D::GetX() const
{
	return m_fX;
}

float Point3D::GetY() const
{
	return m_fY;
}

float Point3D::GetZ() const
{
	return m_fZ;
}

float Point3D::GetDepth() const
{
	return m_fZ;
}

Point Point3D::GetPoint() const
{
	return Point(GetX(), GetY());
}

float &Point3D::X()
{
	return m_fX;
}

const float &Point3D::X() const
{
	return m_fX;
}

float &Point3D::Y()
{
	return m_fY;
}

const float &Point3D::Y() const
{
	return m_fY;
}

float &Point3D::Z()
{
	return m_fZ;
}

const float &Point3D::Z() const
{
	return m_fZ;
}

float Point3D::DistanceFrom(const Point3D &other) const
{
	return (float)nb::System::Sqrt(nb::System::Pow(GetX() - other.GetX(), 2) + nb::System::Pow(GetY() - other.GetY(), 2) + nb::System::Pow(GetZ() - other.GetZ(), 2));
}

Point3DI Point3D::ToPoint3DI() const
{
	return Point3DI((int)GetX(), (int)GetY(), (int)GetZ());
}

Point3DI Point3D::ToRoundPoint3DI() const
{
	return Point3DI(nb::System::Round(GetX()), nb::System::Round(GetY()), nb::System::Round(GetZ()));
}

bool Point3D::Equals(const Point3D &other) const
{
	return *this == other;
}

bool Point3D::IsZero() const
{
	return *this == Zero();
}

bool Point3D::operator == (const Point3D &other) const
{
	return GetX() == other.GetX() && GetY() == other.GetY() && GetZ() == other.GetZ();
}

bool Point3D::operator != (const Point3D &other) const
{
	return !(*this == other);
}

Point3D Point3D::operator + (const Point3D &other) const
{
	return Point3D(GetX() + other.GetX(), GetY() + other.GetY(), GetZ() + other.GetZ());
}

Point3D Point3D::operator + (float f) const
{
	return Point3D(GetX() + f, GetY() + f, GetZ() + f);
}

Point3D Point3D::operator - (const Point3D &other) const
{
	return Point3D(GetX() - other.GetX(), GetY() - other.GetY(), GetZ() - other.GetZ());
}

Point3D Point3D::operator - (float f) const
{
	return Point3D(GetX() - f, GetY() - f, GetZ() - f);
}

Point3D Point3D::operator * (float f) const
{
	return Point3D(GetX() * f, GetY() * f, GetZ() * f);
}

Point3D Point3D::operator / (float f) const
{
	return Point3D(GetX() / f, GetY() / f, GetZ() / f);
}

void Point3D::operator += (const Point3D &other)
{
	return *this = (operator + (other));
}

void Point3D::operator += (float f)
{
	return *this = (operator + (f));
}

void Point3D::operator -= (const Point3D &other)
{
	return *this = (operator - (other));
}

void Point3D::operator -= (float f)
{
	return *this = (operator - (f));
}

void Point3D::operator *= (float f)
{
	return *this = (operator * (f));
}

void Point3D::operator /= (float f)
{
	return *this = (operator / (f));
}

Point3D Point3D::Zero()
{
	return Point3D(0.0f, 0.0f, 0.0f);
}

Point3D Point3D::FromPoint3DI(const Point3DI &other)
{
	return Point3D((float)(other.GetX()), (float)(other.GetY()), (float)(other.GetZ()));
}
