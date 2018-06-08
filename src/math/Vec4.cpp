#include "math/Vec4.h"

using nb::Math::Vec;
using nb::Math::Vec2;
using nb::Math::Vec3;
using nb::Math::Vec4;

Vec4::Vec4()
: Vec(4)
{
	At(0) = 0.0f;
	At(1) = 0.0f;
	At(2) = 0.0f;
	At(3) = 0.0f;
}

Vec4::Vec4(float x, float y, float z, float w)
: Vec(4)
{
	At(0) = x;
	At(1) = y;
	At(2) = z;
	At(3) = w;
}

Vec4::Vec4(const Vec2 &xy, const Vec2 &zw)
: Vec(4)
{
	At(0) = xy.X();
	At(1) = xy.Y();
	At(2) = zw.X();
	At(3) = zw.Y();
}

Vec4::Vec4(float x, const Vec2 &yz, float w)
: Vec(4)
{
	At(0) = x;
	At(1) = yz.X();
	At(2) = yz.Y();
	At(3) = w;
}

Vec4::Vec4(float x, float y, const Vec2 &zw)
: Vec(4)
{
	At(0) = x;
	At(1) = y;
	At(2) = zw.X();
	At(3) = zw.Y();
}

Vec4::Vec4(const Vec3 &xyz, float w)
: Vec(4)
{
	At(0) = xyz.X();
	At(1) = xyz.Y();
	At(2) = xyz.Z();
	At(3) = w;
}

Vec4::Vec4(float x, const Vec3 &yzw)
: Vec(4)
{
	At(0) = x;
	At(1) = yzw.X();
	At(2) = yzw.Y();
	At(3) = yzw.Z();
}

float &Vec4::X()
{
	return At(0);
}

const float &Vec4::X() const
{
	return At(0);
}

float &Vec4::Y()
{
	return At(1);
}

const float &Vec4::Y() const
{
	return At(1);
}

float &Vec4::Z()
{
	return At(2);
}

const float &Vec4::Z() const
{
	return At(2);
}

float &Vec4::W()
{
	return At(3);
}

const float &Vec4::W() const
{
	return At(3);
}

Vec2 Vec4::XY() const
{
	return Vec2(At(0), At(1));
}

Vec2 Vec4::YZ() const
{
	return Vec2(At(1), At(2));
}

Vec2 Vec4::ZW() const
{
	return Vec2(At(2), At(3));
}

Vec3 Vec4::XYZ() const
{
	return Vec3(At(0), At(1), At(2));
}

Vec3 Vec4::YZW() const
{
	return Vec3(At(1), At(2), At(3));
}
