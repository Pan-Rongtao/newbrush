#include "math/Vec3I.h"

using nb::Math::VecI;
using nb::Math::Vec2I;
using nb::Math::Vec3I;

Vec3I::Vec3I()
: VecI(3)
{
	At(0) = 0;
	At(1) = 0;
	At(2) = 0;
}

Vec3I::Vec3I(int x, int y, int z)
: VecI(3)
{
	At(0) = x;
	At(1) = y;
	At(2) = z;
}

Vec3I::Vec3I(const Vec2I &xy, int z)
: VecI(3)
{
	At(0) = xy.X();
	At(1) = xy.Y();
	At(2) = z;
}

Vec3I::Vec3I(int x, const Vec2I &yz)
: VecI(3)
{
	At(0) = x;
	At(1) = yz.X();
	At(2) = yz.Y();
}

int &Vec3I::X()
{
	return At(0);
}

const int &Vec3I::X() const
{
	return At(0);
}

int &Vec3I::Y()
{
	return At(1);
}

const int &Vec3I::Y() const
{
	return At(1);
}

int &Vec3I::Z()
{
	return At(2);
}

const int &Vec3I::Z() const
{
	return At(2);
}

Vec2I Vec3I::XY() const
{
	return Vec2I(At(0), At(1));
}

Vec2I Vec3I::YZ() const
{
	return Vec2I(At(1), At(2));
}

Vec3I Vec3I::CrossProduct(const Vec3I &other) const
{
	return Vec3I(Y() * other.Z() - Z() * other.Y(), Z() * other.X() - X() * other.Z(), X() * other.Y() - Y() * other.X());
}
