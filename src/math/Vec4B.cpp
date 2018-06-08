#include "math/Vec4B.h"

using nb::Math::VecB;
using nb::Math::Vec2B;
using nb::Math::Vec3B;
using nb::Math::Vec4B;

Vec4B::Vec4B()
: VecB(4)
{
	At(0) = 0.0f;
	At(1) = 0.0f;
	At(2) = 0.0f;
	At(3) = 0.0f;
}

Vec4B::Vec4B(bool x, bool y, bool z, bool w)
: VecB(4)
{
	At(0) = x;
	At(1) = y;
	At(2) = z;
	At(3) = w;
}

Vec4B::Vec4B(const Vec2B &xy, const Vec2B &zw)
: VecB(4)
{
	At(0) = xy.X();
	At(1) = xy.Y();
	At(2) = zw.X();
	At(3) = zw.Y();
}

Vec4B::Vec4B(bool x, const Vec2B &yz, bool w)
: VecB(4)
{
	At(0) = x;
	At(1) = yz.X();
	At(2) = yz.Y();
	At(3) = w;
}

Vec4B::Vec4B(bool x, bool y, const Vec2B &zw)
: VecB(4)
{
	At(0) = x;
	At(1) = y;
	At(2) = zw.X();
	At(3) = zw.Y();
}

Vec4B::Vec4B(const Vec3B &xyz, bool w)
: VecB(4)
{
	At(0) = xyz.X();
	At(1) = xyz.Y();
	At(2) = xyz.Z();
	At(3) = w;
}

Vec4B::Vec4B(bool x, const Vec3B &yzw)
: VecB(4)
{
	At(0) = x;
	At(1) = yzw.X();
	At(2) = yzw.Y();
	At(3) = yzw.Z();
}

bool &Vec4B::X()
{
	return At(0);
}

const bool &Vec4B::X() const
{
	return At(0);
}

bool &Vec4B::Y()
{
	return At(1);
}

const bool &Vec4B::Y() const
{
	return At(1);
}

bool &Vec4B::Z()
{
	return At(2);
}

const bool &Vec4B::Z() const
{
	return At(2);
}

bool &Vec4B::W()
{
	return At(3);
}

const bool &Vec4B::W() const
{
	return At(3);
}

Vec2B Vec4B::XY() const
{
	return Vec2B(At(0), At(1));
}

Vec2B Vec4B::YZ() const
{
	return Vec2B(At(1), At(2));
}

Vec2B Vec4B::ZW() const
{
	return Vec2B(At(2), At(3));
}

Vec3B Vec4B::XYZ() const
{
	return Vec3B(At(0), At(1), At(2));
}

Vec3B Vec4B::YZW() const
{
	return Vec3B(At(1), At(2), At(3));
}
