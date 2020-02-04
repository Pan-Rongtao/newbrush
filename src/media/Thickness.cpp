#include "media/Thickness.h"

using namespace nb;

Thickness::Thickness()
	: m_fLeft(0)
	, m_fTop(0)
	, m_fRight(0)
	, m_fBottom(0)
{
}

Thickness::Thickness(float uniform)
{
	reset(uniform, uniform, uniform, uniform);
}

Thickness::Thickness(float left, float top, float right, float bottom)
{
	reset(left, top, right, bottom);
}

Thickness::Thickness(const Thickness &other)
{
	reset(other.m_fLeft, other.m_fTop, other.m_fRight, other.m_fBottom);
}

void Thickness::reset(float left, float top, float right, float bottom)
{
	m_fLeft = left;
	m_fTop = top;
	m_fRight = right;
	m_fBottom = bottom;
}

void Thickness::operator = (const Thickness &other)
{
	reset(other.m_fLeft, other.m_fTop, other.m_fRight, other.m_fBottom);
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

float &Thickness::left()
{
	return m_fLeft;
}

const float &Thickness::left() const
{
	return m_fLeft;
}

float &Thickness::top()
{
	return m_fTop;
}

const float &Thickness::top() const
{
	return m_fTop;
}

float &Thickness::right()
{
	return m_fRight;
}

const float &Thickness::right() const
{
	return m_fRight;
}

float &Thickness::bottom()
{
	return m_fBottom;
}

const float &Thickness::bottom() const
{
	return m_fBottom;
}
