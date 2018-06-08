#include "math/Matrix4x4.h"
#include "core/Exception.h"
#include "system/System.h"

using nb::Math::Matrix;
using nb::Math::Matrix4x4;
using nb::Math::Vec4;

Matrix4x4::Matrix4x4()
: Matrix(4, 4)
{

}

Matrix4x4::Matrix4x4(float m0n0, float m0n1, float m0n2, float m0n3, float m1n0, float m1n1, float m1n2, float m1n3, float m2n0, float m2n1, float m2n2, float m2n3, float m3n0, float m3n1, float m3n2, float m3n3)
: Matrix(4, 4)
{
	At(0, 0) = m0n0; At(0, 1) = m0n1; At(0, 2) = m0n2; At(0, 3) = m0n3;
	At(1, 0) = m1n0; At(1, 1) = m1n1; At(1, 2) = m1n2; At(1, 3) = m1n3;
	At(2, 0) = m2n0; At(2, 1) = m2n1; At(2, 2) = m2n2; At(2, 3) = m2n3;
	At(3, 0) = m3n0; At(3, 1) = m3n1; At(3, 2) = m3n2; At(3, 3) = m3n3;
}

Matrix4x4::Matrix4x4(const Vec4 &m0, const Vec4 &m1, const Vec4 &m2, const Vec4 &m3)
: Matrix(4, 4)
{
	At(0, 0) = m0.X(); At(0, 1) = m0.Y(); At(0, 2) = m0.Z(); At(0, 3) = m0.W();
	At(1, 0) = m1.X(); At(1, 1) = m1.Y(); At(1, 2) = m1.Z(); At(1, 3) = m1.W();
	At(2, 0) = m2.X(); At(2, 1) = m2.Y(); At(2, 2) = m2.Z(); At(2, 3) = m2.W();
	At(3, 0) = m3.X(); At(3, 1) = m3.Y(); At(3, 2) = m3.Z(); At(3, 3) = m3.W();
}

Matrix4x4::Matrix4x4(float *data)
: Matrix(4, 4)
{
}

Matrix4x4::Matrix4x4(float *data, int count)
: Matrix(4, 4)
{
}

void Matrix4x4::ToIdentity()
{
	*this = Identify();
}

Matrix4x4 Matrix4x4::Translate(float offsetX, float offsetY, float offsetZ)
{
	return TranslateMatrix(offsetX, offsetY, offsetZ) * (*this);
}

Matrix4x4 Matrix4x4::TranslateX(float offsetX)
{
	return Translate(offsetX, 0.0f, 0.0f);
}

Matrix4x4 Matrix4x4::TranslateY(float offsetY)
{
	return Translate(0.0f, offsetY, 0.0f);
}

Matrix4x4 Matrix4x4::TranslateZ(float offsetZ)
{
	return Translate(0.0f, 0.0f, offsetZ);
}

Matrix4x4 Matrix4x4::RotateRadian(float radian, float x, float y, float z)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotateRadianX(float radian)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotateRadianY(float radian)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotateRadianZ(float radian)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotateAngle(float angle, float x, float y, float z)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotateAngleX(float angle)
{
	return Matrix4x4
		(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)nb::System::Cos(angle), (float)-nb::System::Sin(angle), 0.0f,
		0.0f, (float)nb::System::Sin(angle), (float)nb::System::Cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f)
	* (*this);
}

Matrix4x4 Matrix4x4::RotateAngleY(float angle)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::RotateAngleZ(float angle)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::Scale(float scaleX, float scaleY, float scaleZ)
{
	return ScaleMatrix(scaleX, scaleY, scaleZ) * (*this);
}

Matrix4x4 Matrix4x4::ScaleX(float scaleX)
{
	return Scale(scaleX, 1.0f, 1.0f);
}

Matrix4x4 Matrix4x4::ScaleY(float scaleY)
{
	return Scale(1.0f, scaleY, 1.0f);
}

Matrix4x4 Matrix4x4::ScaleZ(float scaleZ)
{
	return Scale(1.0f, 1.0f, scaleZ);
}

Matrix4x4 Matrix4x4::ScaleUniform(float uniform)
{
	return Scale(uniform, uniform, uniform);
}

Matrix4x4 Matrix4x4::operator + (float f) const
{
	Matrix4x4 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] += f;
	return ret;
}

Matrix4x4 Matrix4x4::operator + (const Matrix4x4 &other) const
{
	Matrix4x4 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] += other.m_Data[i];
	return ret;
}

Matrix4x4 Matrix4x4::operator - (float f) const
{
	Matrix4x4 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] -= f;
	return ret;
}

Matrix4x4 Matrix4x4::operator - (const Matrix4x4 &other) const
{
	Matrix4x4 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] -= other.m_Data[i];
	return ret;
}

Matrix4x4 Matrix4x4::operator * (float f) const
{
	Matrix4x4 ret(*this);
	for(int i = 0; i != GetColumn() * GetRow(); ++i)
		ret.m_Data[i] *= f;
	return ret;
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4 &right) const
{
	if(!Matrix::CanMultiply(*this, right))
		NB_THROW_EXCEPTION("can not nultiply");

	Matrix4x4 ret;
	for(int i = 0; i != ret.GetColumn(); ++i)
	{
		for(int j = 0; j != ret.GetRow(); ++j)
		{
			for(int k = 0; k != ret.GetRow(); ++k)
				ret.At(i, j) += right.At(i, k) * At(k, j);	//OpenglµÄ³Ë·¨ÊÇ×ó³Ë
		}
	}
	return ret;
}

Matrix4x4 Matrix4x4::Identify()
{
	return Matrix4x4
		(1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::TranslateMatrix(float offsetX, float offsetY, float offsetZ)
{
	return Matrix4x4
		(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		offsetX, offsetY, offsetZ, 1.0f
		);
}

Matrix4x4 Matrix4x4::ScaleMatrix(float scaleX, float scaleY, float scaleZ)
{
	return Matrix4x4
		(scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, scaleY, 0.0f, 0.0f,
		0.0f, 0.0f, scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::RotateMatrix()
{
	return Matrix4x4();
}
