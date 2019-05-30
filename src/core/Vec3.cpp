#include "core/Vec3.h"
#include <math.h>

using namespace nb::core;

Vec3::Vec3()
{
	m_d[0] = 0.0f;
	m_d[1] = 0.0f;
	m_d[2] = 0.0f;
}

Vec3::Vec3(float x, float y, float z)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = z;
}

Vec3::Vec3(const Vec2 &xy, float z)
{
	m_d[0] = xy.x();
	m_d[1] = xy.y();
	m_d[2] = z;
}

Vec3::Vec3(float x, const Vec2 &yz)
{
	m_d[0] = x;
	m_d[1] = yz.x();
	m_d[2] = yz.y();
}

Vec3::Vec3(const Vec3 & other)
{
	*this = other;
}

void Vec3::operator=(const Vec3 & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
}

bool Vec3::operator==(const Vec3 & other) const
{
	return !(operator!=(other));
}

bool Vec3::operator!=(const Vec3 & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2];
}

float &Vec3::operator[](uint32_t index)
{
	return at(index);
}

const float & Vec3::operator[](uint32_t index) const
{
	return at(index);
}

Vec3 Vec3::operator+(float f) const
{
	return operator+(Vec3(f, f, f));
}

Vec3 Vec3::operator+(const Vec3 & v) const
{
	return Vec3(x() + v.x(), y() + v.y(), z() + v.z());
}

Vec3 Vec3::operator-(float f) const
{
	return operator-(Vec3(f, f, f));
}

Vec3 Vec3::operator-(const Vec3 & v) const
{
	return Vec3(x() - v.x(), y() - v.y(), z() - v.z());
}

Vec3 Vec3::operator*(float f) const
{
	return Vec3(x() * f, y() * f, z() * f);
}

Vec3 Vec3::operator/(float f) const
{
	return Vec3(x() / f, y() / f, z() / f);
}

void Vec3::operator+=(float f)
{
	operator+=(Vec3(f, f, f));
}

void Vec3::operator+=(const Vec3 & other)
{
	x() += other.x();
	y() += other.y();
	z() += other.z();
}

void Vec3::operator-=(float f)
{
	operator-=(Vec3(f, f, f));
}

void Vec3::operator-=(const Vec3 & other)
{
	x() -= other.x();
	y() -= other.y();
	z() -= other.z();
}

void Vec3::operator*=(float f)
{
	x() *= f;
	y() *= f;
	z() *= f;
}

void Vec3::operator/=(float f)
{
	x() /= f;
	y() /= f;
	z() /= f;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x(), -y(), -z());
}

float * Vec3::data()
{
	return m_d;
}

const float * Vec3::data() const
{
	return m_d;
}

uint32_t Vec3::dimension() const
{
	return 3;
}

float &Vec3::x()
{
	return m_d[0];
}

const float &Vec3::x() const
{
	return m_d[0];
}

float &Vec3::y()
{
	return m_d[1];
}

const float &Vec3::y() const
{
	return m_d[1];
}

float &Vec3::z()
{
	return m_d[2];
}

const float &Vec3::z() const
{
	return m_d[2];
}

Vec2 Vec3::xy() const
{
	return Vec2(x(), y());
}

Vec2 Vec3::yz() const
{
	return Vec2(y(), z());
}

float & Vec3::at(uint32_t index)
{
	if (index >= dimension())
		NB_THROW_EXCEPTION(std::out_of_range, "index[%d] is out of range [%d, %d)", index, 0, dimension());

	return m_d[index];
}

const float & Vec3::at(uint32_t index) const
{
	return (const_cast<Vec3 *>(this))->operator[](index);
}

float Vec3::norm() const
{
	return (float)sqrt(x() * x() + y() * y() + z() * z());
}

float Vec3::length() const
{
	return norm();
}

Vec3 Vec3::normalized() const
{
	float nor = norm();
	return Vec3(x() / nor, y() / nor, z() / nor);
}

float Vec3::dotProduct(const Vec3 & other) const
{
	return x() * other.x() + y() * other.y() + z() * other.z();
}

Vec3 Vec3::crossProduct(const Vec3 &other) const
{
	return Vec3(y() * other.z() - z() * other.y(), z() * other.x() - x() * other.z(), x() * other.y() - y() * other.x());
}

//class Vec3I

Vec3I::Vec3I()
{
	m_d[0] = 0;
	m_d[1] = 0;
	m_d[2] = 0;
}

Vec3I::Vec3I(int x, int y, int z)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = z;
}

Vec3I::Vec3I(const Vec2I &xy, int z)
{
	m_d[0] = xy.x();
	m_d[1] = xy.y();
	m_d[2] = z;
}

Vec3I::Vec3I(int x, const Vec2I &yz)
{
	m_d[0] = x;
	m_d[1] = yz.x();
	m_d[2] = yz.y();
}

Vec3I::Vec3I(const Vec3I & other)
{
	*this = other;
}

void Vec3I::operator=(const Vec3I & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
}

bool Vec3I::operator==(const Vec3I & other) const
{
	return !(operator!=(other));
}

bool Vec3I::operator!=(const Vec3I & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2];
}

int & Vec3I::operator[](uint32_t index)
{
	return at(index);
}

const int & Vec3I::operator[](uint32_t index) const
{
	return at(index);
}

Vec3I Vec3I::operator+(int n) const
{
	return operator+(Vec3I(n, n, n));
}

Vec3I Vec3I::operator+(const Vec3I & v) const
{
	return Vec3I(x() + v.x(), y() + v.y(), z() + v.z());
}

Vec3I Vec3I::operator-(int n) const
{
	return operator-(Vec3I(n, n, n));
}

Vec3I Vec3I::operator-(const Vec3I & v) const
{
	return Vec3I(x() - v.x(), y() - v.y(), z() - v.z());
}

Vec3I Vec3I::operator*(int n) const
{
	return Vec3I(x() * n, y() * n, z() * n);
}

Vec3I Vec3I::operator/(int n) const
{
	return Vec3I(x() / n, y() / n, z() / n);
}

void Vec3I::operator+=(int n)
{
	operator+=(Vec3I(n, n, n));
}

void Vec3I::operator+=(const Vec3I & other)
{
	x() += other.x();
	y() += other.y();
	z() += other.z();
}

void Vec3I::operator-=(int n)
{
	operator-=(Vec3I(n, n, n));
}

void Vec3I::operator-=(const Vec3I & other)
{
	x() -= other.x();
	y() -= other.y();
	z() -= other.z();
}

void Vec3I::operator*=(int n)
{
	x() *= n;
	y() *= n;
	z() *= n;
}

void Vec3I::operator/=(int n)
{
	x() /= n;
	y() /= n;
	z() /= n;
}

Vec3I Vec3I::operator-() const
{
	return Vec3I(-x(), -y(), -z());
}

int * Vec3I::data()
{
	return m_d;
}

const int * Vec3I::data() const
{
	return m_d;
}

uint32_t Vec3I::dimension() const
{
	return 3;
}

int &Vec3I::x()
{
	return m_d[0];
}

const int &Vec3I::x() const
{
	return m_d[0];
}

int &Vec3I::y()
{
	return m_d[1];
}

const int &Vec3I::y() const
{
	return m_d[1];
}

int &Vec3I::z()
{
	return m_d[2];
}

const int &Vec3I::z() const
{
	return m_d[2];
}

Vec2I Vec3I::xy() const
{
	return Vec2I(x(), y());
}

Vec2I Vec3I::yz() const
{
	return Vec2I(y(), z());
}

int & Vec3I::at(uint32_t index)
{
	if (index >= dimension())
		NB_THROW_EXCEPTION(std::out_of_range, "index[%d] is out of range [%d, %d)", index, 0, dimension());

	return m_d[index];
}

const int & Vec3I::at(uint32_t index) const
{
	return (const_cast<Vec3I *>(this))->operator[](index);
}

float Vec3I::norm() const
{
	return (float)sqrt(x() * x() + y() * y() + z() * z());
}

float Vec3I::lenght() const
{
	return norm();
}

Vec3I Vec3I::normalized() const
{
	float nor = norm();
	return Vec3I((int)(x() / nor), (int)(y() / nor), (int)(z() / nor));
}

Vec3I Vec3I::crossProduct(const Vec3I &other) const
{
	return Vec3I(y() * other.z() - z() * other.y(), z() * other.x() - x() * other.z(), x() * other.y() - y() * other.x());
}


//class Vec3B
Vec3B::Vec3B()
{
	m_d[0] = false;
	m_d[1] = false;
	m_d[2] = false;
}

Vec3B::Vec3B(bool x, bool y, bool z)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = z;
}

Vec3B::Vec3B(const Vec2B &xy, bool z)
{
	m_d[0] = xy.x();
	m_d[1] = xy.y();
	m_d[2] = z;
}

Vec3B::Vec3B(bool x, const Vec2B &yz)
{
	m_d[0] = x;
	m_d[1] = yz.x();
	m_d[2] = yz.y();
}

Vec3B::Vec3B(const Vec3B & other)
{
	*this = other;
}

void Vec3B::operator=(const Vec3B & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
}

bool Vec3B::operator==(const Vec3B & other) const
{
	return !(operator!=(other));
}

bool Vec3B::operator!=(const Vec3B & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2];
}

bool & Vec3B::operator[](uint32_t index)
{
	return at(index);
}

const bool & Vec3B::operator[](uint32_t index) const
{
	return at(index);
}

bool * Vec3B::data()
{
	return m_d;
}

const bool * Vec3B::data() const
{
	return m_d;
}

uint32_t Vec3B::dimension() const
{
	return 3;
}

bool &Vec3B::x()
{
	return m_d[0];
}

const bool &Vec3B::x() const
{
	return m_d[0];
}

bool &Vec3B::y()
{
	return m_d[1];
}

const bool &Vec3B::y() const
{
	return m_d[1];
}

bool &Vec3B::z()
{
	return m_d[2];
}

const bool &Vec3B::z() const
{
	return m_d[2];
}

Vec2B Vec3B::xy() const
{
	return Vec2B(x(), y());
}

Vec2B Vec3B::yz() const
{
	return Vec2B(y(), z());
}

bool & Vec3B::at(uint32_t index)
{
	if (index >= dimension())
		NB_THROW_EXCEPTION(std::out_of_range, "index[%d] is out of range [%d, %d)", index, 0, dimension());

	return m_d[index];
}

const bool & Vec3B::at(uint32_t index) const
{
	return (const_cast<Vec3B *>(this))->operator[](index);
}

float Vec3B::norm() const
{
	return (float)sqrt(x() * x() + y() * y() + z() * z());
}

float Vec3B::lenght() const
{
	return norm();
}

Vec3B Vec3B::crossProduct(const Vec3B & other) const
{
	return Vec3B((bool)(y() * other.z() - z() * other.y()), (bool)(z() * other.x() - x() * other.z()), (bool)(x() * other.y() - y() * other.x()));
}
