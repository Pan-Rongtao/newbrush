#include "core/Vec2.h"
#include "core/Exception.h"
#include <math.h>

using namespace nb::core;

//class Vec2
Vec2::Vec2()
{
	m_d[0] = 0.0f;
	m_d[1] = 0.0f;
}

Vec2::Vec2(float x, float y)
{
	m_d[0] = x;
	m_d[1] = y;
}

Vec2::Vec2(const Vec2 &other)
{
	*this = other;
}

Vec2::~Vec2() 
{
}

void Vec2::operator=(const Vec2 & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
}

bool Vec2::operator==(const Vec2 & other) const
{
	return !(operator!=(other));
}

bool Vec2::operator!=(const Vec2 & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1];
}

float &Vec2::operator[](uint32_t index)
{
	return at(index);
}

const float &Vec2::operator[](uint32_t index) const
{
	return at(index);
}

Vec2 Vec2::operator+(float f) const
{
	return operator+(Vec2(f, f));
}

Vec2 Vec2::operator+(const Vec2 & v) const
{
	return Vec2(x() + v.x(), y() + v.y());
}

Vec2 Vec2::operator-(float f) const
{
	return operator-(Vec2(f, f));
}

Vec2 Vec2::operator-(const Vec2 & v) const
{
	return Vec2(x() - v.x(), y() - v.y());
}

Vec2 Vec2::operator*(float f) const
{
	return Vec2(x() * f, y() * f);
}

Vec2 Vec2::operator/(float f) const
{
	return Vec2(x() / f, y() / f);
}

void Vec2::operator+=(float f)
{
	operator+=(Vec2(f, f));
}

void Vec2::operator+=(const Vec2 & other)
{
	x() += other.x();
	y() += other.y();
}

void Vec2::operator-=(float f)
{
	operator-=(Vec2(f, f));
}

void Vec2::operator-=(const Vec2 & other)
{
	x() -= other.x();
	y() -= other.y();
}

void Vec2::operator*=(float f)
{
	x() *= f;
	y() *= f;
}

void Vec2::operator/=(float f)
{
	x() /= f;
	y() /= f;
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x(), -y());
}

float * Vec2::data()
{
	return m_d;
}

const float * Vec2::data() const
{
	return m_d;
}

uint32_t Vec2::dimension() const
{
	return 2;
}

float &Vec2::x()
{
	return m_d[0];
}

const float &Vec2::x() const
{
	return m_d[0];
}

float &Vec2::y()
{
	return m_d[1];
}

const float &Vec2::y() const
{
	return m_d[1];
}

float & Vec2::at(uint32_t index)
{
	if (index >= dimension())	throw ArrayIndexOutOfRangeException(dimension(), index);
	return m_d[index];
}

const float & Vec2::at(uint32_t index) const
{
	return (const_cast<Vec2 *>(this))->operator[](index);
}

float Vec2::norm() const
{
	return (float)sqrt(x() * x() + y() * y());
}

float Vec2::length() const
{
	return norm();
}

Vec2 Vec2::normalized() const
{
	float nor = norm();
	return Vec2(x() / nor, y() / nor);
}

Vec2 Vec2::crossProduct(const Vec2 &other) const
{
	return Vec2(x() * other.y(), other.x() * y());
}

//class Vec2I

Vec2I::Vec2I()
{
	m_d[0] = 0;
	m_d[1] = 0;
}

Vec2I::Vec2I(int x, int y)
{
	m_d[0] = x;
	m_d[1] = y;
}

Vec2I::Vec2I(const Vec2I &other)
{
	*this = other;
}

Vec2I::~Vec2I()
{
}

void Vec2I::operator=(const Vec2I & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
}

bool Vec2I::operator==(const Vec2I & other) const
{
	return !(operator!=(other));
}

bool Vec2I::operator!=(const Vec2I & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1];
}

int & Vec2I::operator[](uint32_t index)
{
	return at(index);
}

const int & Vec2I::operator[](uint32_t index) const
{
	return at(index);
}

Vec2I Vec2I::operator+(int n) const
{
	return operator+(Vec2I(n, n));
}

Vec2I Vec2I::operator+(const Vec2I & v) const
{
	return Vec2I(x() + v.x(), y() + v.y());
}

Vec2I Vec2I::operator-(int n) const
{
	return operator-(Vec2I(n, n));
}

Vec2I Vec2I::operator-(const Vec2I & v) const
{
	return Vec2I(x() - v.x(), y() - v.y());
}

Vec2I Vec2I::operator*(int n) const
{
	return Vec2I(x() * n, y() * n);
}

Vec2I Vec2I::operator/(int n) const
{
	return Vec2I(x() / n, y() / n);
}

void Vec2I::operator+=(int n)
{
	operator+=(Vec2I(n, n));
}

void Vec2I::operator+=(const Vec2I & other)
{
	x() += other.x();
	y() += other.y();
}

void Vec2I::operator-=(int n)
{
	operator-=(Vec2I(n, n));
}

void Vec2I::operator-=(const Vec2I & other)
{
	x() -= other.x();
	y() -= other.y();
}

void Vec2I::operator*=(int n)
{
	x() *= n;
	y() *= n;
}

void Vec2I::operator/=(int n)
{
	x() /= n;
	y() /= n;
}

Vec2I Vec2I::operator-() const
{
	return Vec2I(-x(), -y());
}

int * Vec2I::data()
{
	return m_d;
}

const int * Vec2I::data() const
{
	return m_d;
}

uint32_t Vec2I::dimension() const
{
	return 2;
}

int &Vec2I::x()
{
	return m_d[0];
}

const int &Vec2I::x() const
{
	return m_d[0];
}

int &Vec2I::y()
{
	return m_d[1];
}

const int &Vec2I::y() const
{
	return m_d[1];
}

int & Vec2I::at(uint32_t index)
{
	if (index >= dimension())	throw ArrayIndexOutOfRangeException(dimension(), index);
	return m_d[index];
}

const int & Vec2I::at(uint32_t index) const
{
	return (const_cast<Vec2I *>(this))->operator[](index);
}

float Vec2I::norm() const
{
	return (float)sqrt(x() * x() + y() * y());
}

float Vec2I::lenght() const
{
	return norm();
}

Vec2I Vec2I::normalized() const
{
	float nor = norm();
	return Vec2I((int)(x() / nor), (int)(y() / nor));
}

Vec2I Vec2I::crossProduct(const Vec2I &other) const
{
	return Vec2I(x() * other.y(), other.x() * y());
}

//class Vec2B

Vec2B::Vec2B()
{
	m_d[0] = false;
	m_d[1] = false;
}

Vec2B::Vec2B(bool x, bool y)
{
	m_d[0] = x;
	m_d[1] = y;
}

Vec2B::Vec2B(const Vec2B &other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
}

Vec2B::~Vec2B()
{
}

void Vec2B::operator=(const Vec2B & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
}

bool Vec2B::operator==(const Vec2B & other) const
{
	return !(operator!=(other));
}

bool Vec2B::operator!=(const Vec2B & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1];
}

bool & Vec2B::operator[](uint32_t index)
{
	return at(index);
}

const bool & Vec2B::operator[](uint32_t index) const
{
	return at(index);
}

bool * Vec2B::data()
{
	return m_d;
}

const bool * Vec2B::data() const
{
	return m_d;
}

uint32_t Vec2B::dimension() const
{
	return 2;
}

bool &Vec2B::x()
{
	return m_d[0];
}

const bool &Vec2B::x() const
{
	return m_d[0];
}

bool &Vec2B::y()
{
	return m_d[1];
}

const bool &Vec2B::y() const
{
	return m_d[1];
}

bool & Vec2B::at(uint32_t index)
{
	if (index >= dimension())	throw ArrayIndexOutOfRangeException(dimension(), index);
	return m_d[index];
}

const bool & Vec2B::at(uint32_t index) const
{
	return (const_cast<Vec2B *>(this))->operator[](index);
}

float Vec2B::norm() const
{
	return (float)sqrt(dimension());
}

float Vec2B::lenght() const
{
	return norm();
}

Vec2B Vec2B::crossProduct(const Vec2B &other) const
{
	return Vec2B((bool)(x() * other.y()), (bool)(other.x() * y()));
}
