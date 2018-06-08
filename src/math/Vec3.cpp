#include "math/Vec3.h"

using nb::Math::Vec;
using nb::Math::Vec2;
using nb::Math::Vec3;

Vec3::Vec3()
: Vec(3)
{
	At(0) = 0.0f;
	At(1) = 0.0f;
	At(2) = 0.0f;
}

Vec3::Vec3(float x, float y, float z)
: Vec(3)
{
	At(0) = x;
	At(1) = y;
	At(2) = z;
}

Vec3::Vec3(const Vec2 &xy, float z)
: Vec(3)
{
	At(0) = xy.X();
	At(1) = xy.Y();
	At(2) = z;
}

Vec3::Vec3(float x, const Vec2 &yz)
: Vec(3)
{
	At(0) = x;
	At(1) = yz.X();
	At(2) = yz.Y();
}

float &Vec3::X()
{
	return At(0);
}

const float &Vec3::X() const
{
	return At(0);
}

float &Vec3::Y()
{
	return At(1);
}

const float &Vec3::Y() const
{
	return At(1);
}

float &Vec3::Z()
{
	return At(2);
}

const float &Vec3::Z() const
{
	return At(2);
}

Vec2 Vec3::XY() const
{
	return Vec2(At(0), At(1));
}

Vec2 Vec3::YZ() const
{
	return Vec2(At(1), At(2));
}

Vec3 Vec3::Normalized() const
{
	Vec3 ret(*this);
	for(int i = 0; i != GetDimension(); ++i)
		ret[i] /= Norm();
	return ret;
}

Vec3 Vec3::CrossProduct(const Vec3 &other) const
{
	return Vec3(Y() * other.Z() - Z() * other.Y(), Z() * other.X() - X() * other.Z(), X() * other.Y() - Y() * other.X());
}

Vec3 Vec3::operator + (const Vec3 &other) const
{
	return Vec3(m_Data[0] + other.m_Data[0], m_Data[1] + other.m_Data[1], m_Data[2] + other.m_Data[2]);
}

Vec3 Vec3::operator - (const Vec3 &other) const
{
	return Vec3(m_Data[0] - other.m_Data[0], m_Data[1] - other.m_Data[1], m_Data[2] - other.m_Data[2]);
}
