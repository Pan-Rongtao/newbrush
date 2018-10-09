#include "core/Vec4.h"
#include "core/Exception.h"
#include <cstring>
#include <math.h>

using namespace nb::core;

//class Vec4
Vec4::Vec4()
{
	m_d[0] = 0.0f;
	m_d[1] = 0.0f;
	m_d[2] = 0.0f;
	m_d[3] = 0.0f;
}

Vec4::Vec4(float x, float y, float z, float w)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = z;
	m_d[3] = w;
}

Vec4::Vec4(const Vec2 &xy, const Vec2 &zw)
{
	m_d[0] = xy.x();
	m_d[1] = xy.y();
	m_d[2] = zw.x();
	m_d[3] = zw.y();
}

Vec4::Vec4(float x, const Vec2 &yz, float w)
{
	m_d[0] = x;
	m_d[1] = yz.x();
	m_d[2] = yz.y();
	m_d[3] = w;
}

Vec4::Vec4(float x, float y, const Vec2 &zw)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = zw.x();
	m_d[3] = zw.y();
}

Vec4::Vec4(const Vec3 &xyz, float w)
{
	m_d[0] = xyz.x();
	m_d[1] = xyz.y();
	m_d[2] = xyz.z();
	m_d[3] = w;
}

Vec4::Vec4(float x, const Vec3 &yzw)
{
	m_d[0] = x;
	m_d[1] = yzw.x();
	m_d[2] = yzw.y();
	m_d[3] = yzw.z();
}

Vec4::Vec4(const Vec4 & other)
{
	*this = other;
}

void Vec4::operator=(const Vec4 & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
	m_d[3] = other.m_d[3];
}

bool Vec4::operator==(const Vec4 & other) const
{
	return !(operator!=(other));
}

bool Vec4::operator!=(const Vec4 & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2] || m_d[3] != other.m_d[3];
}

float & Vec4::operator[](uint32_t index)
{
	return at(index);
}

const float & Vec4::operator[](uint32_t index) const
{
	return at(index);
}

Vec4 Vec4::operator+(float f) const
{
	return operator+(Vec4(f, f, f, f));
}

Vec4 Vec4::operator+(const Vec4 & v) const
{
	return Vec4(x() + v.x(), y() + v.y(), z() + v.z(), w() + v.w());
}

Vec4 Vec4::operator-(float f) const
{
	return operator-(Vec4(f, f, f, f));
}

Vec4 Vec4::operator-(const Vec4 & v) const
{
	return Vec4(x() - v.x(), y() - v.y(), z() - v.z(), w() - v.w());
}

Vec4 Vec4::operator*(float f) const
{
	return Vec4(x() * f, y() * f, z() * f, w() * f);
}

Vec4 Vec4::operator/(float f) const
{
	return Vec4(x() / f, y() / f, z() / f, w() / f);
}

void Vec4::operator+=(float f)
{
	operator+=(Vec4(f, f, f, f));
}

void Vec4::operator+=(const Vec4 & other)
{
	x() += other.x();
	y() += other.y();
	z() += other.z();
	w() += other.w();
}

void Vec4::operator-=(float f)
{
	operator-=(Vec4(f, f, f, f));
}

void Vec4::operator-=(const Vec4 & other)
{
	x() -= other.x();
	y() -= other.y();
	z() -= other.z();
	w() -= other.w();
}

void Vec4::operator*=(float f)
{
	x() *= f;
	y() *= f;
	z() *= f;
	w() *= f;
}

void Vec4::operator/=(float f)
{
	x() /= f;
	y() /= f;
	z() /= f;
	w() /= f;
}

Vec4 Vec4::operator-() const
{
	return Vec4(-x(), -y(), -z(), -w());
}

float * Vec4::data()
{
	return m_d;
}

const float * Vec4::data() const
{
	return m_d;
}

uint32_t Vec4::dimension() const
{
	return 4;
}

float &Vec4::x()
{
	return m_d[0];
}

const float &Vec4::x() const
{
	return m_d[0];
}

float &Vec4::y()
{
	return m_d[1];
}

const float &Vec4::y() const
{
	return m_d[1];
}

float &Vec4::z()
{
	return m_d[2];
}

const float &Vec4::z() const
{
	return m_d[2];
}

float &Vec4::w()
{
	return m_d[3];
}

const float &Vec4::w() const
{
	return m_d[3];
}

Vec2 Vec4::xy() const
{
	return Vec2(x(), y());
}

Vec2 Vec4::yz() const
{
	return Vec2(y(), z());
}

Vec2 Vec4::zw() const
{
	return Vec2(z(), w());
}

Vec3 Vec4::xyz() const
{
	return Vec3(x(), y(), z());
}

Vec3 Vec4::yzw() const
{
	return Vec3(x(), y(), z());
}

float & Vec4::at(uint32_t index)
{
	if (index >= dimension())	throw ArrayIndexOutOfRangeException(dimension(), index);
	return m_d[index];
}

const float & Vec4::at(uint32_t index) const
{
	return (const_cast<Vec4 *>(this))->operator[](index);
}

float Vec4::norm() const
{
	return (float)sqrt(x() * x() + y() * y() + z() * z() + w() * w());
}

float Vec4::length() const
{
	return norm();
}

Vec4 Vec4::normalized() const
{
	float nor = norm();
	return Vec4(x() / nor, y() / nor, z() / nor, w() / nor);
}

//class Vec4I
Vec4I::Vec4I()
{
	m_d[0] = 0;
	m_d[1] = 0;
	m_d[2] = 0;
	m_d[3] = 0;
}

Vec4I::Vec4I(int x, int y, int z, int w)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = z;
	m_d[3] = w;
}

Vec4I::Vec4I(const Vec2I &xy, const Vec2I &zw)
{
	m_d[0] = xy.x();
	m_d[1] = xy.y();
	m_d[2] = zw.x();
	m_d[3] = zw.y();
}

Vec4I::Vec4I(int x, const Vec2I &yz, int w)
{
	m_d[0] = x;
	m_d[1] = yz.x();
	m_d[2] = yz.y();
	m_d[3] = w;
}

Vec4I::Vec4I(int x, int y, const Vec2I &zw)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = zw.x();
	m_d[3] = zw.y();
}

Vec4I::Vec4I(const Vec3I &xyz, int w)
{
	m_d[0] = xyz.x();
	m_d[1] = xyz.y();
	m_d[2] = xyz.z();
	m_d[3] = w;
}

Vec4I::Vec4I(int x, const Vec3I &yzw)
{
	m_d[0] = x;
	m_d[1] = yzw.x();
	m_d[2] = yzw.y();
	m_d[3] = yzw.z();
}

Vec4I::Vec4I(const Vec4I & other)
{
	*this = other;
}

void Vec4I::operator=(const Vec4I & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
	m_d[3] = other.m_d[3];
}

bool Vec4I::operator==(const Vec4I & other) const
{
	return !(operator!=(other));
}

bool Vec4I::operator!=(const Vec4I & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2] || m_d[3] != other.m_d[3];
}

int & Vec4I::operator[](uint32_t index)
{
	return at(index);
}

const int & Vec4I::operator[](uint32_t index) const
{
	return at(index);
}

Vec4I Vec4I::operator+(int n) const
{
	return operator+(Vec4I(n, n, n, n));
}

Vec4I Vec4I::operator+(const Vec4I & v) const
{
	return Vec4I(x() + v.x(), y() + v.y(), z() + v.z(), w() + v.w());
}

Vec4I Vec4I::operator-(int n) const
{
	return operator-(Vec4I(n, n, n, n));
}

Vec4I Vec4I::operator-(const Vec4I & v) const
{
	return Vec4I(x() - v.x(), y() - v.y(), z() - v.z(), w() - v.w());
}

Vec4I Vec4I::operator*(int n) const
{
	return Vec4I(x() * n, y() * n, z() * n, w() * n);
}

Vec4I Vec4I::operator/(int n) const
{
	return Vec4I(x() / n, y() / n, z() / n, w() / n);
}

void Vec4I::operator+=(int n)
{
	operator+=(Vec4I(n, n, n, n));
}

void Vec4I::operator+=(const Vec4I & other)
{
	x() += other.x();
	y() += other.y();
	z() += other.z();
	w() += other.w();
}

void Vec4I::operator-=(int n)
{
	operator-=(Vec4I(n, n, n, n));
}

void Vec4I::operator-=(const Vec4I & other)
{
	x() -= other.x();
	y() -= other.y();
	z() -= other.z();
	w() -= other.w();
}

void Vec4I::operator*=(int n)
{
	x() *= n;
	y() *= n;
	z() *= n;
	w() *= n;
}

void Vec4I::operator/=(int n)
{
	x() /= n;
	y() /= n;
	z() /= n;
	w() /= n;
}

Vec4I Vec4I::operator-() const
{
	return Vec4I(-x(), -y(), -z(), -w());
}

int * Vec4I::data()
{
	return m_d;
}

const int * Vec4I::data() const
{
	return m_d;
}

uint32_t Vec4I::dimension() const
{
	return 4;
}

int &Vec4I::x()
{
	return m_d[0];
}

const int &Vec4I::x() const
{
	return m_d[0];
}

int &Vec4I::y()
{
	return m_d[1];
}

const int &Vec4I::y() const
{
	return m_d[1];
}

int &Vec4I::z()
{
	return m_d[2];
}

const int &Vec4I::z() const
{
	return m_d[2];
}

int &Vec4I::w()
{
	return m_d[3];
}

const int &Vec4I::w() const
{
	return m_d[3];
}

Vec2I Vec4I::xy() const
{
	return Vec2I(x(), y());
}

Vec2I Vec4I::yz() const
{
	return Vec2I(y(), z());
}

Vec2I Vec4I::zw() const
{
	return Vec2I(z(), w());
}

Vec3I Vec4I::xyz() const
{
	return Vec3I(x(), y(), z());
}

Vec3I Vec4I::yzw() const
{
	return Vec3I(x(), y(), z());
}

int & Vec4I::at(uint32_t index)
{
	if (index >= dimension())	throw ArrayIndexOutOfRangeException(dimension(), index);
	return m_d[index];
}

const int & Vec4I::at(uint32_t index) const
{
	return (const_cast<Vec4I *>(this))->operator[](index);
}

float Vec4I::norm() const
{
	return (float)sqrt(x() * x() + y() * y() + z() * z() + w() * w());
}

float Vec4I::lenght() const
{
	return norm();
}

Vec4I Vec4I::normalized() const
{
	float nor = norm();
	return Vec4I((int)(x() / nor), (int)(y() / nor), (int)(z() / nor), (int)(w() / nor));
}

//class Vec4B
Vec4B::Vec4B()
{
	m_d[0] = false;
	m_d[1] = false;
	m_d[2] = false;
	m_d[3] = false;
}

Vec4B::Vec4B(bool x, bool y, bool z, bool w)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = z;
	m_d[3] = w;
}

Vec4B::Vec4B(const Vec2B &xy, const Vec2B &zw)
{
	m_d[0] = xy.x();
	m_d[1] = xy.y();
	m_d[2] = zw.x();
	m_d[3] = zw.y();
}

Vec4B::Vec4B(bool x, const Vec2B &yz, bool w)
{
	m_d[0] = x;
	m_d[1] = yz.x();
	m_d[2] = yz.y();
	m_d[3] = w;
}

Vec4B::Vec4B(bool x, bool y, const Vec2B &zw)
{
	m_d[0] = x;
	m_d[1] = y;
	m_d[2] = zw.x();
	m_d[3] = zw.y();
}

Vec4B::Vec4B(const Vec3B &xyz, bool w)
{
	m_d[0] = xyz.x();
	m_d[1] = xyz.y();
	m_d[2] = xyz.z();
	m_d[3] = w;
}

Vec4B::Vec4B(bool x, const Vec3B &yzw)
{
	m_d[0] = x;
	m_d[1] = yzw.x();
	m_d[2] = yzw.y();
	m_d[3] = yzw.z();
}

Vec4B::Vec4B(const Vec4B & other)
{
	*this = other;
}

void Vec4B::operator=(const Vec4B & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
	m_d[3] = other.m_d[3];
}

bool Vec4B::operator==(const Vec4B & other) const
{
	return !(operator!=(other));
}

bool Vec4B::operator!=(const Vec4B & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2] || m_d[3] != other.m_d[3];
}

bool & Vec4B::operator[](uint32_t index)
{
	return at(index);
}

const bool & Vec4B::operator[](uint32_t index) const
{
	return at(index);
}

bool * Vec4B::data()
{
	return m_d;
}

const bool * Vec4B::data() const
{
	return m_d;
}

uint32_t Vec4B::dimension() const
{
	return 4;
}

bool &Vec4B::x()
{
	return m_d[0];
}

const bool &Vec4B::x() const
{
	return m_d[0];
}

bool &Vec4B::y()
{
	return m_d[1];
}

const bool &Vec4B::y() const
{
	return m_d[1];
}

bool &Vec4B::z()
{
	return m_d[2];
}

const bool &Vec4B::z() const
{
	return m_d[2];
}

bool &Vec4B::w()
{
	return m_d[3];
}

const bool &Vec4B::w() const
{
	return m_d[3];
}

Vec2B Vec4B::xy() const
{
	return Vec2B(x(), y());
}

Vec2B Vec4B::yz() const
{
	return Vec2B(y(), z());
}

Vec2B Vec4B::zw() const
{
	return Vec2B(z(), w());
}

Vec3B Vec4B::xyz() const
{
	return Vec3B(x(), y(), z());
}

Vec3B Vec4B::yzw() const
{
	return Vec3B(y(), z(), w());
}

bool & Vec4B::at(uint32_t index)
{
	if (index >= dimension())	throw ArrayIndexOutOfRangeException(dimension(), index);
	return m_d[index];
}

const bool & Vec4B::at(uint32_t index) const
{
	return (const_cast<Vec4B *>(this))->operator[](index);
}

float Vec4B::norm() const
{
	return (float)sqrt(x() * x() + y() * y() + z() * z() + w() * w());
}

float Vec4B::lenght() const
{
	return norm();
}
