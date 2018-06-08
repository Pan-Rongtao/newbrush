#include "math/Vec4I.h"

using nb::Math::VecI;
using nb::Math::Vec2I;
using nb::Math::Vec3I;
using nb::Math::Vec4I;

Vec4I::Vec4I()
: VecI(4)
{
	At(0) = 0;
	At(1) = 0;
	At(2) = 0;
	At(3) = 0;
}

Vec4I::Vec4I(int x, int y, int z, int w)
: VecI(4)
{
	At(0) = x;
	At(1) = y;
	At(2) = z;
	At(3) = w;
}

Vec4I::Vec4I(const Vec2I &xy, const Vec2I &zw)
: VecI(4)
{
	At(0) = xy.X();
	At(1) = xy.Y();
	At(2) = zw.X();
	At(3) = zw.Y();
}

Vec4I::Vec4I(int x, const Vec2I &yz, int w)
: VecI(4)
{
	At(0) = x;
	At(1) = yz.X();
	At(2) = yz.Y();
	At(3) = w;
}

Vec4I::Vec4I(int x, int y, const Vec2I &zw)
: VecI(4)
{
	At(0) = x;
	At(1) = y;
	At(2) = zw.X();
	At(3) = zw.Y();
}

Vec4I::Vec4I(const Vec3I &xyz, int w)
: VecI(4)
{
	At(0) = xyz.X();
	At(1) = xyz.Y();
	At(2) = xyz.Z();
	At(3) = w;
}

Vec4I::Vec4I(int x, const Vec3I &yzw)
: VecI(4)
{
	At(0) = x;
	At(1) = yzw.X();
	At(2) = yzw.Y();
	At(3) = yzw.Z();
}

int &Vec4I::X()
{
	return At(0);
}

const int &Vec4I::X() const
{
	return At(0);
}

int &Vec4I::Y()
{
	return At(1);
}

const int &Vec4I::Y() const
{
	return At(1);
}

int &Vec4I::Z()
{
	return At(2);
}

const int &Vec4I::Z() const
{
	return At(2);
}

int &Vec4I::W()
{
	return At(3);
}

const int &Vec4I::W() const
{
	return At(3);
}

Vec2I Vec4I::XY() const
{
	return Vec2I(At(0), At(1));
}

Vec2I Vec4I::YZ() const
{
	return Vec2I(At(1), At(2));
}

Vec2I Vec4I::ZW() const
{
	return Vec2I(At(2), At(3));
}

Vec3I Vec4I::XYZ() const
{
	return Vec3I(At(0), At(1), At(2));
}

Vec3I Vec4I::YZW() const
{
	return Vec3I(At(1), At(2), At(3));
}
