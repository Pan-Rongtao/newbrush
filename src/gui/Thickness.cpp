#include "gui/Thickness.h"
using namespace nb::gui;

Thickness::Thickness()
	: m_fLeft(0)
	, m_fTop(0)
	, m_fRight(0)
	, m_fBottom(0)
{
}

Thickness::Thickness(float uniform)
{
	Reset(uniform, uniform, uniform, uniform);
}

Thickness::Thickness(float left, float top, float right, float bottom)
{
	Reset(left, top, right, bottom);
}

Thickness::Thickness(const Thickness &other)
{
	Reset(other.m_fLeft, other.m_fTop, other.m_fRight, other.m_fBottom);
}

void Thickness::Reset(float left, float top, float right, float bottom)
{
	m_fLeft = left;
	m_fTop = top;
	m_fRight = right;
	m_fBottom = bottom;
}

void Thickness::operator = (const Thickness &other)
{
	Reset(other.m_fLeft, other.m_fTop, other.m_fRight, other.m_fBottom);
}

bool Thickness::operator == (const Thickness &other) const
{
	return m_fLeft == other.m_fLeft && m_fTop == other.m_fTop && m_fRight == other.m_fRight && m_fBottom == other.m_fBottom;
}

bool Thickness::operator != (const Thickness &other) const
{
	return !(*this == other);
}

Thickness Thickness::operator - (float f) const
{
	return Thickness(m_fLeft - f, m_fTop - f, m_fRight - f, m_fBottom - f);
}

void Thickness::operator -= (float f)
{
	operator = (operator -(f));
}

Thickness Thickness::operator + (float f) const
{
	return Thickness(m_fLeft + f, m_fTop + f, m_fRight + f, m_fBottom + f);
}

void Thickness::operator += (float f)
{
	operator = (operator +(f));
}

float &Thickness::Left()
{
	return m_fLeft;
}

const float &Thickness::Left() const
{
	return m_fLeft;
}

float &Thickness::Top()
{
	return m_fTop;
}

const float &Thickness::Top() const
{
	return m_fTop;
}

float &Thickness::Right()
{
	return m_fRight;
}

const float &Thickness::Right() const
{
	return m_fRight;
}

float &Thickness::Bottom()
{
	return m_fBottom;
}

const float &Thickness::Bottom() const
{
	return m_fBottom;
}

bool Thickness::Equals(const Thickness &other) const
{
	return *this == other;
}
