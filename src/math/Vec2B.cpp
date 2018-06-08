#include "math/Vec2B.h"

using nb::Math::VecB;
using nb::Math::Vec2B;

Vec2B::Vec2B()
: VecB(2)
{
	At(0) = 0.0f;
	At(1) = 0.0f;
}

Vec2B::Vec2B(bool x, bool y)
: VecB(2)
{
	At(0) = x;
	At(1) = y;
}

Vec2B::Vec2B(const Vec2B &other)
: VecB(2)
{
	At(0) = other.At(0);
	At(1) = other.At(1);
}

Vec2B::~Vec2B()
{
}

bool &Vec2B::X()
{
	return At(0);
}

const bool &Vec2B::X() const
{
	return At(0);
}

bool &Vec2B::Y()
{
	return At(1);
}

const bool &Vec2B::Y() const
{
	return At(1);
}
