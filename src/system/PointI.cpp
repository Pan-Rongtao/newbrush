#include "system/System.h"
#include "system/PointI.h"

using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(PointI, ValueObject, &ValueObject::IsEqualFun<PointI>, &ValueObject::CopyFun<PointI>);

//use Real when define
PointI::PointI()
{
	SetXY(0, 0);
}

PointI::PointI(const PointI &other)
{
	SetXY(other.GetX(), other.GetY());
}

PointI::PointI(int x, int y)
{
	SetXY(x, y);
}

PointI::~PointI()
{

}

void PointI::operator = (const PointI &p)
{
	SetXY(p.GetX(), p.GetY());
}

bool PointI::operator == (const PointI &p) const
{
	return GetX() == p.GetX() && GetY() == p.GetY();
}

bool PointI::operator != (const PointI &p) const
{
	return !(*this == p);
}

PointI PointI::operator + (const PointI &p) const
{
	return PointI(GetX() + p.GetX(), GetY() + p.GetY());
}

PointI PointI::operator + (int n) const
{
	return PointI(GetX() + n, GetY() + n);
}

PointI PointI::operator - (const PointI &p) const
{
	return PointI(GetX() - p.GetX(), GetY() - p.GetY());
}

PointI PointI::operator - (int n) const
{
	return PointI(GetX() - n, GetY() - n);
}

PointI PointI::operator * (int n) const
{
	return PointI(GetX() * n, GetY() * n);
}

PointI PointI::operator * (float f) const
{
	return PointI((int)(GetX() * f), (int)(GetY() * f));
}
//除以0的异常
PointI PointI::operator / (int n) const
{
	return PointI(GetX() / n, GetY() / n);
}

PointI PointI::operator / (float f) const
{
	return PointI((int)(GetX() / f), (int)(GetY() / f));
}

void PointI::operator += (const PointI &p)
{
	*this = (operator +(p));
}

void PointI::operator += (int n)
{
	*this = (operator +(n));
}

void PointI::operator -= (const PointI &p)
{
	*this = (operator -(p));
}

void PointI::operator -= (int n)
{
	*this = (operator -(n));
}

void PointI::operator *= (int n)
{
	*this = (operator *(n));
}

void PointI::operator *= (float f)
{
	*this = (operator *(f));
}

void PointI::operator /= (int n)
{
	*this = (operator /(n));
}

void PointI::operator /= (float f)
{
	*this = (operator / (f));
}

void PointI::SetX(int x)
{
	m_nX = x;
}

void PointI::SetY(int y)
{
	m_nY = y;
}

void PointI::SetXY(int x, int y)
{
	SetX(x);
	SetY(y);
}

int PointI::GetX() const
{
	return m_nX;
}

int PointI::GetY() const
{
	return m_nY;
}

bool PointI::IsZero() const
{
	return *this == Zero();
}

bool PointI::IsNegative() const
{
	return GetX() < 0 && GetY() < 0;
}

int &PointI::X()
{
	return m_nX;
}

const int &PointI::X() const
{
	return m_nX;
}

int &PointI::Y()
{
	return m_nY;
}

const int &PointI::Y() const
{
	return m_nY;
}

PointI PointI::Exchange()
{
	return PointI(GetY(), GetX());
}

int PointI::DistanceFrom(const PointI &other) const
{
	return (int)(nb::System::Sqrt(nb::System::Pow(float(GetX() - other.GetX()), 2) + nb::System::Pow(float(GetY() - other.GetY()), 2)));
}

int PointI::ManHattanLength(const PointI &other) const
{
	return nb::System::Abs(GetX() - other.GetX()) + nb::System::Abs(GetY() - other.GetY());
}

bool PointI::Equals(const PointI &p) const
{
	return *this == p;
}

PointI PointI::MultiplyRound(float f) const
{
	return PointI(nb::System::Round(GetX() * f), nb::System::Round(GetY() * f));
}

PointI PointI::DivideRound(float f) const
{
	return PointI(nb::System::Round(GetX() / f), nb::System::Round(GetY() / f));
}

PointI PointI::Zero()
{
	return PointI(0, 0);
}
