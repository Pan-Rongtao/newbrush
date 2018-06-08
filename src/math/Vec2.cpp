#include "math/Vec2.h"

using nb::Math::Vec;
using nb::Math::Vec2;

Vec2::Vec2()
: Vec(2)
{
	At(0) = 0.0f;
	At(1) = 0.0f;
}

Vec2::Vec2(float x, float y)
: Vec(2)
{
	At(0) = x;
	At(1) = y;
}

Vec2::Vec2(const Vec2 &other)
: Vec(2)
{
	At(0) = other.At(0);
	At(1) = other.At(1);
}

Vec2::~Vec2()
{
}

float &Vec2::X()
{
	return At(0);
}

const float &Vec2::X() const
{
	return At(0);
}

float &Vec2::Y()
{
	return At(1);
}

const float &Vec2::Y() const
{
	return At(1);
}

Vec2 Vec2::Normalized() const
{
	Vec2 ret(*this);
	for(int i = 0; i != GetDimension(); ++i)
		ret[i] /= Norm();
	return ret;
}

Vec2 Vec2::CrossProduct(const Vec2 &other) const
{
	Vec2 ret(X()* other.Y(), other.X() * Y());
	return ret;
}
