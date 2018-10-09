#include "core/Matrix3x3.h"
#include "core/Exception.h"
#include <cstring>

using namespace nb::core;

Matrix3x3::Matrix3x3()
{
}

Matrix3x3::Matrix3x3(float m0n0, float m0n1, float m0n2, float m1n0, float m1n1, float m1n2, float m2n0, float m2n1, float m2n2)
{
	m_d[0] = Vec3(m0n0, m0n1, m0n2);
	m_d[1] = Vec3(m1n0, m1n1, m1n2);
	m_d[2] = Vec3(m2n0, m2n1, m2n2);
}

Matrix3x3::Matrix3x3(const Vec3 &m0, const Vec3 &m1, const Vec3 &m2)
{
	m_d[0] = m0;
	m_d[1] = m1;
	m_d[2] = m2;
}

Matrix3x3::Matrix3x3(float *data)
{
	m_d[0][0] = data[0]; m_d[0][1] = data[1]; m_d[0][2] = data[2];
	m_d[1][0] = data[3]; m_d[1][1] = data[4]; m_d[1][2] = data[5];
	m_d[2][0] = data[6]; m_d[2][1] = data[7]; m_d[2][2] = data[8];
}

Matrix3x3::Matrix3x3(float *data, uint32_t count)
{
	if (count > size())	count = size();
	memcpy(this->data(), data, count * sizeof(float));
}

Matrix3x3 Matrix3x3::identity()
{
	return Matrix3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix3x3::Matrix3x3(const Matrix3x3 & other)
{
	*this = other;
}

void Matrix3x3::operator=(const Matrix3x3 & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
}

bool Matrix3x3::operator==(const Matrix3x3 & other) const
{
	return !(operator!=(other));
}

bool Matrix3x3::operator!=(const Matrix3x3 & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2];
}

Vec3 & Matrix3x3::operator[](uint32_t row)
{
	if (row >= this->row())	throw ArrayIndexOutOfRangeException(row, this->row());
	return m_d[row];
}

const Vec3 & Matrix3x3::operator[](uint32_t row) const
{
	return const_cast<Matrix3x3 *>(this)->operator[](row);
}

Matrix3x3 Matrix3x3::operator + (float f) const
{
	return Matrix3x3(m_d[0] + f, m_d[1] + f, m_d[2] + f);
}

Matrix3x3 Matrix3x3::operator + (const Matrix3x3 &other) const
{
	return Matrix3x3(m_d[0] + other.m_d[0], m_d[1] + other.m_d[1], m_d[2] + other.m_d[2]);
}

Matrix3x3 Matrix3x3::operator - (float f) const
{
	return Matrix3x3(m_d[0] - f, m_d[1] - f, m_d[2] - f);
}

Matrix3x3 Matrix3x3::operator - (const Matrix3x3 &other) const
{
	return Matrix3x3(m_d[0] - other.m_d[0], m_d[1] - other.m_d[1], m_d[2] - other.m_d[2]);
}

Matrix3x3 Matrix3x3::operator * (float f) const
{
	return Matrix3x3(m_d[0] * f, m_d[1] * f, m_d[2] * f);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 & right) const
{
	Matrix3x3 ret;
	for (int i = 0; i != column(); ++i)
	{
		for (int j = 0; j != row(); ++j)
		{
			for (int k = 0; k != row(); ++k)
				ret.at(i, j) += right.at(i, k) * at(k, j);	//OpenglµÄ³Ë·¨ÊÇ×ó³Ë
		}
	}
	return ret;
}

Matrix3x3 Matrix3x3::operator/(float f) const
{
	return Matrix3x3(m_d[0] / f, m_d[1] / f, m_d[2] / f);
}

float * Matrix3x3::data()
{
	return m_d[0].data();
}

const float * Matrix3x3::data() const
{
	return m_d[0].data();
}

uint32_t Matrix3x3::size() const
{
	return 9;
}

uint32_t Matrix3x3::row() const
{
	return 3;
}

uint32_t Matrix3x3::column() const
{
	return 3;
}

float & Matrix3x3::at(uint32_t row, uint32_t col)
{
	return (*this)[row][col];
}

const float & Matrix3x3::at(uint32_t row, uint32_t col) const
{
	return (*this)[row][col];
}

bool Matrix3x3::isIdentity() const
{
	return *this == identity();
}

void Matrix3x3::toIdentity()
{
	*this = identity();
}
/*
void Matrix3x3::translate(float x, float y)
{
	translateX(x);
	translateY(y);
}

void Matrix3x3::translateX(float x)
{

}

void Matrix3x3::translateY(float y)
{

}

void Matrix3x3::rotateRadian(float radian, float x, float y)
{
	rotateRadianX(x);
	rotateRadianY(y);
}

void Matrix3x3::rotateRadianX(float radian)
{

}

void Matrix3x3::rotateRadianY(float radian)
{

}

void Matrix3x3::rotateAngle(float angle, float x, float y)
{
	rotateAngleX(x);
	rotateAngleY(y);
}

void Matrix3x3::rotateAngleX(float angle)
{

}

void Matrix3x3::rotateAngleY(float angle)
{

}

void Matrix3x3::scale(float x, float y)
{
	scaleX(x);
	scaleY(y);
}

void Matrix3x3::scaleX(float x)
{

}

void Matrix3x3::scaleY(float y)
{

}
*/
