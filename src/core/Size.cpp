#include "core/Size.h"
#include <algorithm>
#include <math.h>

using namespace nb::core;

////////////////////class Size
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

void Size::operator = (const Size &other)
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

void Size::setWidth(float width)
{
	m_width = width;
}

void Size::setHeight(float height)
{
	m_height = height;
}

void Size::reset(float width, float height)
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

Size &Size::swap()
{
	std::swap(m_width, m_height);
	return *this;
}

Size Size::narrow(const Size &other) const
{
	return Size(std::min(width(), other.width()), std::min(height(), other.height()));
}

Size Size::expand(const Size &other) const
{
	return Size(std::max(width(), other.width()), std::max(height(), other.height()));
}

bool Size::equals(const Size &other) const
{
	return *this == other;
}

////////////////class SizeI
SizeI::SizeI()
	: SizeI(0, 0)
{
}

SizeI::SizeI(int width, int height)
	: m_width(width)
	, m_height(height)
{
}

SizeI::SizeI(const SizeI &other)
	: SizeI(other.width(), other.height())
{
}

SizeI SizeI::zero()
{
	return SizeI(0, 0);
}

void SizeI::operator = (const SizeI &other)
{
	m_width = other.width();
	m_height = other.height();
}

bool SizeI::operator == (const SizeI &other) const
{
	return !(operator != (other));
}

bool SizeI::operator != (const SizeI &other) const
{
	return m_width != other.width() || m_height != other.height();
}

SizeI SizeI::operator + (const SizeI &other) const
{
	return SizeI(width() + other.width(), height() + other.height());
}

SizeI SizeI::operator + (int n) const
{
	return SizeI(width() + n, height() + n);
}

SizeI SizeI::operator - (const SizeI &other) const
{
	return SizeI(width() - other.width(), height() - other.height());
}

SizeI SizeI::operator - (int n) const
{
	return SizeI(width() - n, height() - n);
}

SizeI SizeI::operator * (int n) const
{
	return SizeI(width() * n, height() * n);
}

SizeI SizeI::operator * (float n) const
{
	return SizeI((int)(width() * n), (int)(height() * n));
}

SizeI SizeI::operator / (int n) const
{
	return operator /((float)n);
}

SizeI SizeI::operator / (float d) const
{
	if (d == 0.0f)
		NB_THROW_EXCEPTION(std::invalid_argument, "divisor is 0");

	return SizeI((int)(width() / d), (int)(height() / d));
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

void SizeI::setWidth(int width)
{
	m_width = width;
}

void SizeI::setHeight(int height)
{
	m_height = height;
}

void SizeI::reset(int width, int height)
{
	setWidth(width);
	setHeight(height);
}

int &SizeI::width()
{
	return m_width;
}

const int &SizeI::width() const
{
	return m_width;
}

int &SizeI::height()
{
	return m_height;
}

const int &SizeI::height() const
{
	return m_height;
}

bool SizeI::isZero() const
{
	return *this == zero();
}

bool SizeI::isNegative() const
{
	return width() < 0 && height() < 0;
}

SizeI &SizeI::swap()
{
	std::swap(m_width, m_height);
	return *this;
}

SizeI SizeI::narrow(const SizeI &other) const
{
	return SizeI(std::min(width(), other.width()), std::min(height(), other.height()));
}

SizeI SizeI::expand(const SizeI &other) const
{
	return SizeI(std::max(width(), other.width()), std::max(height(), other.height()));
}

bool SizeI::equals(const SizeI &other) const
{
	return *this == other;
}

SizeI SizeI::multiplyRound(float f) const
{
	return SizeI((int)std::round(width() * f), (int)std::round(height() * f));
}

SizeI SizeI::divideRound(float f) const
{
	return SizeI((int)std::round(width() / f), (int)std::round(height() / f));
}
