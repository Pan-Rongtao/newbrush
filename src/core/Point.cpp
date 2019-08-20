#include "core/Point.h"
#include <math.h>

using namespace nb::core;

//////////////////class Point
Point::Point()
	: Point(0.0f, 0.0f)
{
}

Point::Point(float x, float y)
	: m_x(x)
	, m_y(y)
{
}

Point::Point(const Point &other)
	: Point(other.x(), other.y())
{
}

Point Point::zero()
{
	return Point(0.0f, 0.0f);
}

void Point::operator = (const Point &p) &
{
	m_x = p.x();
	m_y = p.y();
}

bool Point::operator == (const Point &p) const
{
	return !(operator != (p));
}

bool Point::operator != (const Point &p) const
{
	return m_x != p.x() || m_y != p.y();
}

Point Point::operator + (const Point &p) const
{
	return Point(x() + p.x(), y() + p.y());
}

Point Point::operator + (float f) const
{
	return Point(x() + f, y() + f);
}

Point Point::operator - (const Point &p) const
{
	return Point(x() - p.x(), y() - p.y());
}

Point Point::operator - (float f) const
{
	return Point(x() - f, y() - f);
}

Point Point::operator * (float f) const
{
	return Point(x() * f, y() * f);
}

Point Point::operator / (float f) const
{
	if (f == 0.0f)
		nbThrowException(std::invalid_argument, "divisor is 0");

	return Point(x() / f, y() / f);
}

void Point::operator += (const Point &p) &
{
	*this = (operator +(p));
}

void Point::operator += (float f) &
{
	*this = (operator +(f));
}

void Point::operator -= (const Point &p) &
{
	*this = (operator -(p));
}

void Point::operator -= (float f) &
{
	*this = (operator -(f));
}

void Point::operator *= (float f) &
{
	*this = (operator *(f));
}

void Point::operator /= (float f) &
{
	*this = (operator /(f));
}

void Point::setX(float x) &
{
	m_x = x;
}

void Point::setY(float y) &
{
	m_y = y;
}

void Point::reset(float x, float y) &
{
	setX(x);
	setY(y);
}

float &Point::x()
{
	return m_x;
}

const float &Point::x() const
{
	return m_x;
}

float &Point::y()
{
	return m_y;
}

const float &Point::y() const
{
	return m_y;
}

bool Point::isZero() const
{
	return *this == zero();
}

bool Point::isNegative() const
{
	return x() < 0.0f && y() < 0.0f;
}

float Point::distance(const Point &other) const
{
	return std::hypotf(x() - other.x(), y() - other.y());
}

float Point::manhattanLength(const Point &other) const
{
	return std::abs(x() - other.x()) + std::abs(y() - other.y());
}
