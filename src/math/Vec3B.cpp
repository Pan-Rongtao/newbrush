#include "math/Vec3B.h"

using nb::Math::VecB;
using nb::Math::Vec2B;
using nb::Math::Vec3B;

Vec3B::Vec3B()
: VecB(3)
{
	At(0) = 0.0f;
	At(1) = 0.0f;
	At(2) = 0.0f;
}

Vec3B::Vec3B(bool x, bool y, bool z)
: VecB(3)
{
	At(0) = x;
	At(1) = y;
	At(2) = z;
}

Vec3B::Vec3B(const Vec2B &xy, bool z)
: VecB(3)
{
	At(0) = xy.X();
	At(1) = xy.Y();
	At(2) = z;
}

Vec3B::Vec3B(bool x, const Vec2B &yz)
: VecB(3)
{
	At(0) = x;
	At(1) = yz.X();
	At(2) = yz.Y();
}

bool &Vec3B::X()
{
	return At(0);
}

const bool &Vec3B::X() const
{
	return At(0);
}

bool &Vec3B::Y()
{
	return At(1);
}

const bool &Vec3B::Y() const
{
	return At(1);
}

bool &Vec3B::Z()
{
	return At(2);
}

const bool &Vec3B::Z() const
{
	return At(2);
}

Vec2B Vec3B::XY() const
{
	return Vec2B(At(0), At(1));
}

Vec2B Vec3B::YZ() const
{
	return Vec2B(At(1), At(2));
}
