#include "newbrush/core/base/Point.h"
#include <cmath>

using namespace nb;

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
	auto floatEqual = [](float a, float b)->bool {
		return fabs(a - b) <= 1e-6;
	};
	return !floatEqual(m_x, p.x()) || !floatEqual(m_y, p.y());
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

//////////////////////class Point3D
Point3D::Point3D()
	: Point3D(0.0f, 0.0f, 0.0f)
{
}

Point3D::Point3D(float x, float y, float z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{
}

Point3D::Point3D(const Point &p, float z)
	: Point3D(p.x(), p.y(), z)
{
}

Point3D::Point3D(const Point3D &other)
	: Point3D(other.x(), other.y(), other.z())
{
}

Point3D Point3D::zero()
{
	return Point3D(0.0f, 0.0f, 0.0f);
}

void Point3D::operator = (const Point3D &other)
{
	m_x = other.x();
	m_y = other.y();
	m_z = other.z();
}

bool Point3D::operator == (const Point3D &other) const
{
	return !(operator !=(other));
}

bool Point3D::operator != (const Point3D &other) const
{
	return x() != other.x() || y() != other.y() || z() != other.z();
}

Point3D Point3D::operator + (const Point3D &other) const
{
	return Point3D(x() + other.x(), y() + other.y(), z() + other.z());
}

Point3D Point3D::operator + (float f) const
{
	return Point3D(x() + f, y() + f, z() + f);
}

Point3D Point3D::operator - (const Point3D &other) const
{
	return Point3D(x() - other.x(), y() - other.y(), z() - other.z());
}

Point3D Point3D::operator - (float f) const
{
	return Point3D(x() - f, y() - f, z() - f);
}

Point3D Point3D::operator * (float f) const
{
	return Point3D(x() * f, y() * f, z() * f);
}

Point3D Point3D::operator / (float f) const
{
	if (f == 0.0f)
		nbThrowException(std::invalid_argument, "divisor is 0");

	return Point3D(x() / f, y() / f, z() / f);
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

void Point3D::setX(float x) &
{
	m_x = x;
}

void Point3D::setY(float y) &
{
	m_y = y;
}

void Point3D::setZ(float z) &
{
	m_z = z;
}

void Point3D::setXY(float x, float y) &
{
	setX(x);
	setY(y);
}

void Point3D::reset(float x, float y, float z) &
{
	setX(x);
	setY(y);
	setZ(z);
}

float &Point3D::x()
{
	return m_x;
}

const float &Point3D::x() const
{
	return m_x;
}

float &Point3D::y()
{
	return m_y;
}

const float &Point3D::y() const
{
	return m_y;
}

float &Point3D::z()
{
	return m_z;
}

const float &Point3D::z() const
{
	return m_z;
}

Point Point3D::xy() const
{
	return Point(x(), y());
}

float Point3D::distance(const Point3D &other) const
{
	return (float)sqrt(pow(x() - other.x(), 2) + pow(y() - other.y(), 2) + pow(z() - other.z(), 2));
}

bool Point3D::isZero() const
{
	return *this == zero();
}