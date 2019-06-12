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

void Point::operator = (const Point &p)
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

void Point::operator += (const Point &p)
{
	*this = (operator +(p));
}

void Point::operator += (float f)
{
	*this = (operator +(f));
}

void Point::operator -= (const Point &p)
{
	*this = (operator -(p));
}

void Point::operator -= (float f)
{
	*this = (operator -(f));
}

void Point::operator *= (float f)
{
	*this = (operator *(f));
}

void Point::operator /= (float f)
{
	*this = (operator /(f));
}

void Point::setX(float x)
{
	m_x = x;
}

void Point::setY(float y)
{
	m_y = y;
}

void Point::reset(float x, float y)
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

Point &Point::swap()
{
	std::swap(m_x, m_y);
	return *this;
}

float Point::distance(const Point &other) const
{
	return (float)sqrt(pow(x() - other.x(), 2) + pow(y() - other.y(), 2));
}

float Point::manhattanLength(const Point &other) const
{
	return abs(x() - other.x()) + abs(y() - other.y());
}

bool Point::equals(const Point &p) const
{
	return *this == p;
}

///////////////class PointI
PointI::PointI()
	: PointI(0, 0)
{
}

PointI::PointI(int x, int y)
	: m_x(x)
	, m_y(y)
{
}

PointI::PointI(const PointI &other)
	: PointI(other.x(), other.y())
{
}

PointI PointI::zero()
{
	return PointI(0, 0);
}

void PointI::operator = (const PointI &p)
{
	m_x = p.x();
	m_y = p.y();
}

bool PointI::operator == (const PointI &p) const
{
	return !(operator != (p));
}

bool PointI::operator != (const PointI &p) const
{
	return m_x != p.x() || m_y != p.y();
}

PointI PointI::operator + (const PointI &p) const
{
	return PointI(x() + p.x(), y() + p.y());
}

PointI PointI::operator + (int n) const
{
	return PointI(x() + n, y() + n);
}

PointI PointI::operator - (const PointI &p) const
{
	return PointI(x() - p.x(), y() - p.y());
}

PointI PointI::operator - (int n) const
{
	return PointI(x() - n, y() - n);
}

PointI PointI::operator * (int n) const
{
	return PointI(x() * n, y() * n);
}

PointI PointI::operator * (float f) const
{
	return PointI((int)(x() * f), (int)(y() * f));
}

PointI PointI::operator / (int n) const
{
	return operator /((float)n);
}

PointI PointI::operator / (float f) const
{
	if (f == 0.0f)
		nbThrowException(std::invalid_argument, "divisor is 0");

	return PointI((int)(x() / f), (int)(y() / f));
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

void PointI::setX(int x)
{
	m_x = x;
}

void PointI::setY(int y)
{
	m_y = y;
}

void PointI::reset(int x, int y)
{
	setX(x);
	setY(y);
}

int &PointI::x()
{
	return m_x;
}

const int &PointI::x() const
{
	return m_x;
}

int &PointI::y()
{
	return m_y;
}

const int &PointI::y() const
{
	return m_y;
}

bool PointI::isZero() const
{
	return *this == zero();
}

bool PointI::isNegative() const
{
	return x() < 0 && y() < 0;
}

PointI &PointI::swap()
{
	std::swap(m_x, m_y);
	return *this;
}

int PointI::distance(const PointI &other) const
{
	return (int)(sqrt(pow(float(x() - other.x()), 2) + pow(float(y() - other.y()), 2)));
}

int PointI::manhattanLength(const PointI &other) const
{
	return abs(x() - other.x()) + abs(y() - other.y());
}

bool PointI::equals(const PointI &p) const
{
	return *this == p;
}

PointI PointI::multiplyRound(float f) const
{
	return PointI((int)std::round(x() * f), (int)std::round(y() * f));
}

PointI PointI::divideRound(float f) const
{
	return PointI((int)std::round(x() / f), (int)std::round(y() / f));
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

void Point3D::setX(float x)
{
	m_x = x;
}

void Point3D::setY(float y)
{
	m_y = y;
}

void Point3D::setZ(float z)
{
	m_z = z;
}

void Point3D::setXY(float x, float y)
{
	setX(x);
	setY(y);
}

void Point3D::reset(float x, float y, float z)
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

bool Point3D::equals(const Point3D &other) const
{
	return *this == other;
}

bool Point3D::isZero() const
{
	return *this == zero();
}

////////////////////class Point3DI
Point3DI::Point3DI()
	: Point3DI(0, 0, 0)
{
}

Point3DI::Point3DI(int x, int y, int z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{
}

Point3DI::Point3DI(const PointI &p, int z)
	: Point3DI(p.x(), p.y(), z)
{
}

Point3DI::Point3DI(const Point3DI &other)
	: Point3DI(other.x(), other.y(), other.z())
{
}

Point3DI Point3DI::zero()
{
	return Point3DI(0, 0, 0);
}

void Point3DI::operator = (const Point3DI &other)
{
	m_x = other.x();
	m_y = other.y();
	m_z = other.z();
}

bool Point3DI::operator == (const Point3DI &other) const
{
	return !(operator !=(other));
}

bool Point3DI::operator != (const Point3DI &other) const
{
	return x() == other.x() && y() == other.y() && z() == other.z();
}

Point3DI Point3DI::operator + (const Point3DI &other) const
{
	return Point3DI(x() + other.x(), y() + other.y(), z() + other.z());
}

Point3DI Point3DI::operator + (int n) const
{
	return Point3DI(x() + n, y() + n, z() + n);
}

Point3DI Point3DI::operator - (const Point3DI &other) const
{
	return Point3DI(x() - other.x(), y() - other.y(), z() - other.z());
}

Point3DI Point3DI::operator - (int n) const
{
	return Point3DI(x() - n, y() - n, z() - n);
}

Point3DI Point3DI::operator * (int n) const
{
	return Point3DI(x() * n, y() * n, z() * n);
}

Point3DI Point3DI::operator * (float f) const
{
	return Point3DI((int)(x() * f), (int)(y() * f), (int)(z() * f));
}

Point3DI Point3DI::operator / (int n) const
{
	return operator /((float)n);
}

Point3DI Point3DI::operator / (float f) const
{
	if (f == 0.0f)
		nbThrowException(std::invalid_argument, "divisor is 0");

	return Point3DI((int)(x() / f), (int)(y() / f), (int)(z() / f));
}

void Point3DI::operator += (const Point3DI &other)
{
	return *this = (operator + (other));
}

void Point3DI::operator += (int n)
{
	return *this = (operator + (n));
}

void Point3DI::operator -= (const Point3DI &other)
{
	return *this = (operator - (other));
}

void Point3DI::operator -= (int n)
{
	return *this = (operator - (n));
}

void Point3DI::operator *= (int n)
{
	return *this = (operator * (n));
}

void Point3DI::operator *= (float f)
{
	return *this = (operator * (f));
}

void Point3DI::operator /= (int n)
{
	return *this = (operator / (n));
}

void Point3DI::operator /= (float f)
{
	return *this = (operator / (f));
}

void Point3DI::setX(int x)
{
	m_x = x;
}

void Point3DI::setY(int y)
{
	m_y = y;
}

void Point3DI::setZ(int z)
{
	m_z = z;
}

void Point3DI::setXY(int x, int y)
{
	setX(x);
	setY(y);
}

void Point3DI::reset(int x, int y, int z)
{
	setX(x);
	setY(y);
	setZ(z);
}

int &Point3DI::x()
{
	return m_x;
}

const int &Point3DI::x() const
{
	return m_x;
}

int &Point3DI::y()
{
	return m_y;
}

const int &Point3DI::y() const
{
	return m_y;
}

int &Point3DI::z()
{
	return m_z;
}

const int &Point3DI::z() const
{
	return m_z;
}

PointI Point3DI::xy() const
{
	return PointI(x(), y());
}

bool Point3DI::isZero() const
{
	return *this == zero();
}

int Point3DI::distance(const Point3DI &other) const
{
	return (int)(sqrt(pow(float(x() - other.x()), 2) + pow(float(y() - other.y()), 2) + pow((float)(z() - other.z()), 2)));
}

bool Point3DI::equals(const Point3DI &other) const
{
	return *this == other;
}

Point3DI Point3DI::multiplyRound(float f) const
{
	return Point3DI((int)std::round(x() * f), (int)std::round(y() * f), (int)std::round(z() * f));
}

Point3DI Point3DI::divideRound(float f) const
{
	return Point3DI((int)std::round(x() / f), (int)std::round(y() / f), (int)std::round(z() / f));
}
