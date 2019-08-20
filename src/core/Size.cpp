#include "core/Size.h"
#include <algorithm>
#include <math.h>

using namespace nb::core;

Size::Size()
	: Size(0.0f, 0.0f)
{
}

Size::Size(float width, float height)
	: m_width(width)
	, m_height(height)
{
}

Size::Size(const Size &other)
	: Size(other.width(), other.height())
{
}

Size Size::zero()
{
	return Size(0.0f, 0.0f);
}

void Size::operator = (const Size &other) &
{
	m_width = other.width();
	m_height = other.height();
}

bool Size::operator == (const Size &other) const
{
	return !(operator !=(other));
}

bool Size::operator != (const Size &other) const
{
	return m_width != other.width() || m_height != other.height();
}

Size Size::operator + (const Size &other) const
{
	return Size(width() + other.width(), height() + other.height());
}

Size Size::operator + (float f) const
{
	return Size(width() + f, height() + f);
}

Size Size::operator - (const Size &other) const
{
	return Size(width() - other.width(), height() - other.height());
}

Size Size::operator - (float f) const
{
	return Size(width() - f, height() - f);
}

Size Size::operator * (float f) const
{
	return Size(width() * f, height() * f);
}

Size Size::operator / (float f) const
{
	return Size(width() / f, height() / f);
}

void Size::operator += (const Size &other) &
{
	*this = (operator +(other));
}

void Size::operator += (float f) &
{
	*this = (operator +(f));
}

void Size::operator -= (const Size &other) &
{
	*this = (operator -(other));
}

void Size::operator -= (float f) &
{
	*this = (operator -(f));
}

void Size::operator *= (float f) &
{
	*this = (operator *(f));
}

void Size::operator /= (float f) &
{
	*this = (operator /(f));
}

void Size::setWidth(float width) &
{
	m_width = width;
}

void Size::setHeight(float height) &
{
	m_height = height;
}

void Size::reset(float width, float height) &
{
	setWidth(width);
	setHeight(height);
}

float &Size::width()
{
	return m_width;
}

const float &Size::width() const
{
	return m_width;
}

float &Size::height()
{
	return m_height;
}

const float &Size::height() const
{
	return m_height;
}

bool Size::isZero() const
{
	return *this == zero();
}

bool Size::isNegative() const
{
	return m_width < 0.0f && m_height < 0.0f;
}

Size Size::narrow(const Size &other) const
{
	return Size(std::min(width(), other.width()), std::min(height(), other.height()));
}

Size Size::expand(const Size &other) const
{
	return Size(std::max(width(), other.width()), std::max(height(), other.height()));
}
