#include "math/Matrix3x3.h"
#include "core/Exception.h"

using nb::Math::Matrix;
using nb::Math::Matrix3x3;
using nb::Math::Vec3;

Matrix3x3::Matrix3x3()
: Matrix(3, 3)
{

}

Matrix3x3::Matrix3x3(float m0n0, float m0n1, float m0n2, float m1n0, float m1n1, float m1n2, float m2n0, float m2n1, float m2n2)
: Matrix(3, 3)
{
	At(0, 0) = m0n0; At(0, 1) = m0n1; At(0, 2) = m0n2;
	At(1, 0) = m1n0; At(1, 1) = m1n1; At(1, 2) = m1n2;
	At(2, 0) = m2n0; At(2, 1) = m2n1; At(2, 2) = m2n2;
}

Matrix3x3::Matrix3x3(const Vec3 &m0, const Vec3 &m1, const Vec3 &m2)
: Matrix(3, 3)
{
	At(0, 0) = m0.X(); At(0, 1) = m0.Y(); At(0, 2) = m0.Z();
	At(1, 0) = m1.X(); At(1, 1) = m1.Y(); At(1, 2) = m1.Z();
	At(2, 0) = m2.X(); At(2, 1) = m2.Y(); At(2, 2) = m2.Z();
}

Matrix3x3::Matrix3x3(float *data)
: Matrix(3, 3)
{
}

Matrix3x3::Matrix3x3(float *data, int count)
: Matrix(3, 3)
{
}

void Matrix3x3::ToIdentity()
{
	*this = Identity();
}

void Matrix3x3::Translate(float x, float y)
{
	TranslateX(x);
	TranslateY(y);
}

void Matrix3x3::TranslateX(float x)
{

}

void Matrix3x3::TranslateY(float y)
{

}

void Matrix3x3::RotateRadian(float radian, float x, float y)
{
	RotateRadianX(x);
	RotateRadianY(y);
}

void Matrix3x3::RotateRadianX(float radian)
{

}

void Matrix3x3::RotateRadianY(float radian)
{

}

void Matrix3x3::RotateAngle(float angle, float x, float y)
{
	RotateAngleX(x);
	RotateAngleY(y);
}

void Matrix3x3::RotateAngleX(float angle)
{

}

void Matrix3x3::RotateAngleY(float angle)
{

}

void Matrix3x3::Scale(float x, float y)
{
	ScaleX(x);
	ScaleY(y);
}

void Matrix3x3::ScaleX(float x)
{

}

void Matrix3x3::ScaleY(float y)
{

}

Matrix3x3 Matrix3x3::operator + (float f) const
{
	Matrix3x3 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] += f;
	return ret;
}

Matrix3x3 Matrix3x3::operator + (const Matrix3x3 &other) const
{
	Matrix3x3 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] += other.m_Data[i];
	return ret;
}

Matrix3x3 Matrix3x3::operator - (float f) const
{
	Matrix3x3 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] -= f;
	return ret;
}

Matrix3x3 Matrix3x3::operator - (const Matrix3x3 &other) const
{
	Matrix3x3 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] -= other.m_Data[i];
	return ret;
}

Matrix3x3 Matrix3x3::operator * (float f) const
{
	Matrix3x3 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] *= f;
	return ret;
}

Matrix3x3 Matrix3x3::operator * (const Matrix &right) const
{
	if(!Matrix::CanMultiply(*this, right))
		NB_THROW_EXCEPTION("can not nultiply");

	return Matrix3x3
		(
		);
}

Matrix3x3 Matrix3x3::Identity()
{
	return Matrix3x3
		(1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f);
}
