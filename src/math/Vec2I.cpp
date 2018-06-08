#include "math/Vec2I.h"

using nb::Math::VecI;
using nb::Math::Vec2I;

Vec2I::Vec2I()
: VecI(2)
{
	At(0) = 0;
	At(1) = 0;
}

Vec2I::Vec2I(int x, int y)
: VecI(2)
{
	At(0) = x;
	At(1) = y;
}

Vec2I::Vec2I(const Vec2I &other)
: VecI(2)
{
	At(0) = other.At(0);
	At(1) = other.At(1);
}

Vec2I::~Vec2I()
{
}

int &Vec2I::X()
{
	return At(0);
}

const int &Vec2I::X() const
{
	return At(0);
}

int &Vec2I::Y()
{
	return At(1);
}

const int &Vec2I::Y() const
{
	return At(1);
}

Vec2I Vec2I::CrossProduct(const Vec2I &other) const
{
	Vec2I ret(X()* other.Y(), other.X() * Y());
	return ret;
}
