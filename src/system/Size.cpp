#include <assert.h>
#include "system/System.h"
#include "system/Size.h"

using namespace nb::System;

//use Real when define
Size::Size()
{
	ReSize(0.0, 0.0);
}

Size::Size(const Size &other)
{
	ReSize(other.GetWidth(), other.GetHeight());
}

Size::Size(float width, float height)
{
	ReSize(width, height);
}

Size::~Size()
{

}

void Size::operator = (const Size &other)
{
	ReSize(other.GetWidth(), other.GetHeight());
}

bool Size::operator == (const Size &other) const
{
	return GetWidth() == other.GetWidth() && GetHeight() == other.GetHeight();
}

bool Size::operator != (const Size &other) const
{
	return !(*this == other);
}

Size Size::operator + (const Size &other) const
{
	return Size(GetWidth() + other.GetWidth(), GetHeight() + other.GetHeight());
}

Size Size::operator + (float f) const
{
	return Size(GetWidth() + f, GetHeight() + f);
}

Size Size::operator - (const Size &other) const
{
	return Size(GetWidth() - other.GetWidth(), GetHeight() - other.GetHeight());
}

Size Size::operator - (float f) const
{
	return Size(GetWidth() - f, GetHeight() - f);
}

Size Size::operator * (float f) const
{
	return Size(GetWidth() * f, GetHeight() * f);
}

Size Size::operator / (float f) const
{
	return Size(GetWidth() / f, GetHeight() / f);
}

void Size::operator += (const Size &other)
{
	*this = (operator +(other));
}

void Size::operator += (float f)
{
	*this = (operator +(f));
}

void Size::operator -= (const Size &other)
{
	*this = (operator -(other));
}

void Size::operator -= (float f)
{
	*this = (operator -(f));
}

void Size::operator *= (float f)
{
	*this = (operator *(f));
}

void Size::operator /= (float f)
{
	*this = (operator /(f));
}

void Size::SetWidth(float width)
{
	m_fWidth = width;
}

void Size::SetHeight(float height)
{
	m_fHeight = height;
}

void Size::ReSize(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

float Size::GetWidth() const
{
	return m_fWidth;
}

float Size::GetHeight() const
{
	return m_fHeight;
}

bool Size::IsZero() const
{
	return *this == Zero();
}

bool Size::IsNegative() const
{
	return GetWidth() < 0.0f && GetHeight() <= 0.0f;
}

float &Size::Width()
{
	return m_fWidth;
}

const float &Size::Width() const
{
	return m_fWidth;
}

float &Size::Height()
{
	return m_fHeight;
}

const float &Size::Height() const
{
	return m_fHeight;
}

Size Size::Exchange()
{
	return Size(m_fHeight, m_fWidth);
}

Size Size::NarrowWith(const Size &other) const
{
	return Size(nb::System::Min(GetWidth(), other.GetWidth()), nb::System::Min(GetHeight(), other.GetHeight()));
}

Size Size::ExpandWith(const Size &other) const
{
	return Size(nb::System::Max(GetWidth(), other.GetWidth()), nb::System::Max(GetHeight(), other.GetHeight()));
}

SizeI Size::ToSizeI() const
{
	return SizeI((int)GetWidth(), (int)GetHeight());
}

SizeI Size::ToRoundSizeI() const
{
	return SizeI(nb::System::Round(GetWidth()), nb::System::Round(GetHeight()));
}

bool Size::Equals(const Size &other) const
{
	return *this == other;
}

Size Size::Zero()
{
	return Size(0.0, 0.0);
}

Size Size::FromSizeI(const SizeI &size)
{
	return Size((float)(size.GetWidth()), (float)(size.GetHeight()));
}
