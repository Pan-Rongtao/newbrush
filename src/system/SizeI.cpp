#include <assert.h>
#include "system/System.h"
#include "system/SizeI.h"

using namespace nb::System;

//use Real when define
SizeI::SizeI()
{
	Resize(0, 0);
}

SizeI::SizeI(const SizeI &other)
{
	Resize(other.GetWidth(), other.GetHeight());
}

SizeI::SizeI(int width, int height)
{
	Resize(width, height);
}

SizeI::~SizeI()
{

}

void SizeI::operator = (const SizeI &other)
{
	Resize(other.GetWidth(), other.GetHeight());
}

bool SizeI::operator == (const SizeI &other) const
{
	return GetWidth() == other.GetWidth() && GetHeight() == other.GetHeight();
}

bool SizeI::operator != (const SizeI &other) const
{
	return !(*this == other);
}

SizeI SizeI::operator + (const SizeI &other) const
{
	return SizeI(GetWidth() + other.GetWidth(), GetHeight() + other.GetHeight());
}

SizeI SizeI::operator + (int n) const
{
	return SizeI(GetWidth() + n, GetHeight() + n);
}

SizeI SizeI::operator - (const SizeI &other) const
{
	return SizeI(GetWidth() - other.GetWidth(), GetHeight() - other.GetHeight());
}

SizeI SizeI::operator - (int n) const
{
	return SizeI(GetWidth() - n, GetHeight() - n);
}

SizeI SizeI::operator * (int n) const
{
	return SizeI(GetWidth() * n, GetHeight() * n);
}

SizeI SizeI::operator * (float n) const
{
	return SizeI((int)(GetWidth() * n), (int)(GetHeight() * n));
}
//if define assert
SizeI SizeI::operator / (int n) const
{
	assert(n != 0);
	return SizeI(GetWidth() / n, GetHeight() / n);
}

SizeI SizeI::operator / (float d) const
{
	assert(d != 0.0);
	return SizeI((int)(GetWidth() / d), (int)(GetHeight() / d));
}

void SizeI::operator += (const SizeI &other)
{
	*this = (operator +(other));
}

void SizeI::operator += (int n)
{
	*this = (operator +(n));
}

void SizeI::operator -= (const SizeI &other)
{
	*this = (operator -(other));
}

void SizeI::operator -= (int n)
{
	*this = (operator -(n));
}

void SizeI::operator *= (int n)
{
	*this = (operator *(n));
}

void SizeI::operator *= (float n)
{
	*this = (operator *(n));
}

void SizeI::operator /= (int n)
{
	*this = (operator /(n));
}

void SizeI::operator /= (float d)
{
	*this = (operator / (d));
}

void SizeI::SetWidth(int width)
{
	m_nWidth = width;
}

void SizeI::SetHeight(int height)
{
	m_nHeight = height;
}

void SizeI::Resize(int width, int height)
{
	SetWidth(width);
	SetHeight(height);
}

int SizeI::GetWidth() const
{
	return m_nWidth;
}

int SizeI::GetHeight() const
{
	return m_nHeight;
}

bool SizeI::IsZero() const
{
	return *this == Zero();
}

bool SizeI::IsNegative() const
{
	return GetWidth() < 0 && GetHeight() < 0;
}

int &SizeI::Width()
{
	return m_nWidth;
}

const int &SizeI::Width() const
{
	return m_nWidth;
}

int &SizeI::Height()
{
	return m_nHeight;
}

const int &SizeI::Height() const
{
	return m_nHeight;
}

SizeI SizeI::Exchange()
{
	return SizeI(m_nHeight, m_nWidth);
}

SizeI SizeI::NarrowWith(const SizeI &other) const
{
	return SizeI(nb::System::Min(GetWidth(), other.GetWidth()), nb::System::Min(GetHeight(), other.GetHeight()));
}

SizeI SizeI::ExpandWith(const SizeI &other) const
{
	return SizeI(nb::System::Max(GetWidth(), other.GetWidth()), nb::System::Max(GetHeight(), other.GetHeight()));
}

bool SizeI::Equals(const SizeI &other) const
{
	return *this == other;
}

SizeI SizeI::MultiplyRound(float f) const
{
	return SizeI(nb::System::Round(GetWidth() * f), nb::System::Round(GetHeight() * f));
}

SizeI SizeI::DivideRound(float f) const
{
	return SizeI(nb::System::Round(GetWidth() / f), nb::System::Round(GetHeight() / f));
}

SizeI SizeI::Zero()
{
	return SizeI(0, 0);
}
