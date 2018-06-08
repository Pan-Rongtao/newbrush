#include "math/Matrix2x2.h"
#include "core/Exception.h"

using nb::Math::Matrix;
using nb::Math::Matrix2x2;
using nb::Math::Vec2;

Matrix2x2::Matrix2x2()
: Matrix(2, 2)
{
}

Matrix2x2::Matrix2x2(float m0n0, float m0n1, float m1n0, float m1n1)
: Matrix(2, 2)
{
	At(0, 0) = m0n0; At(0, 1) = m0n1;
	At(1, 0) = m1n0; At(1, 1) = m1n1;
}

Matrix2x2::Matrix2x2(const Vec2 &m0, const Vec2 &m1)
: Matrix(2, 2)
{
	At(0, 0) = m0.X(); At(0, 1) = m0.Y();
	At(1, 0) = m1.X(); At(1, 1) = m1.Y();
}

Matrix2x2::Matrix2x2(float *data)
: Matrix(2, 2, data)
{
}

Matrix2x2::Matrix2x2(float *data, int count)
: Matrix(2, 2, data, count)
{
}

Matrix2x2 Matrix2x2::operator + (float f) const
{
	Matrix2x2 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] += f;
	return ret;
}

Matrix2x2 Matrix2x2::operator + (const Matrix2x2 &other) const
{
	Matrix2x2 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] += other.m_Data[i];
	return ret;
}

Matrix2x2 Matrix2x2::operator - (float f) const
{
	Matrix2x2 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] -= f;
	return ret;
}

Matrix2x2 Matrix2x2::operator - (const Matrix2x2 &other) const
{
	Matrix2x2 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] -= other.m_Data[i];
	return ret;
}

Matrix2x2 Matrix2x2::operator * (float f) const
{
	Matrix2x2 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] *= f;
	return ret;
}

Matrix2x2 Matrix2x2::operator * (const Matrix &right) const
{
	if(!Matrix::CanMultiply(*this, right))
		NB_THROW_EXCEPTION("can not nultiply");

	return Matrix2x2
		(
		);
}

void Matrix2x2::ToIdentity()
{
	*this = Identity();
}

Matrix2x2 Matrix2x2::Identity()
{
	return Matrix2x2
		(1.0f, 0.0f,
		 0.0f, 1.0f);
}

