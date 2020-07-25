#include "newbrush/core/Thickness.h"

using namespace nb;

Thickness::Thickness()
	: Thickness(0, 0, 0, 0)
{
}

Thickness::Thickness(float uniform)
	: Thickness(uniform, uniform, uniform, uniform)
{
}

Thickness::Thickness(float _left, float _top, float _right, float _bottom)
	: left(_left)
	, top(_top)
	, right(_right)
	, bottom(_bottom)
{
}

void Thickness::reset(float _left, float _top, float _right, float _bottom)
{
	left = _left;
	top = _top;
	right = _right;
	bottom = _bottom;
}

bool Thickness::operator == (const Thickness &other) const
{
	return left == other.left && top == other.top && right == other.right && bottom == other.bottom;
}

bool Thickness::operator != (const Thickness &other) const
{
	return !(*this == other);
}

Thickness Thickness::operator - (float f) const
{
	return Thickness(left - f, top - f, right - f, bottom - f);
}

void Thickness::operator -= (float f)
{
	operator = (operator -(f));
}

Thickness Thickness::operator + (float f) const
{
	return Thickness(left + f, top + f, right + f, bottom + f);
}

void Thickness::operator += (float f)
{
	operator = (operator +(f));
}

Thickness Thickness::operator * (float f) const
{
	return Thickness(left * f, top * f, right * f, bottom * f);
}

void Thickness::operator *= (float f)
{
	operator = (operator *(f));
}
