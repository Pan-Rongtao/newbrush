#include "core/Matrix4x4.h"
#include <cstring>
#include <math.h>

using namespace nb::core;

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(float m0n0, float m0n1, float m0n2, float m0n3, float m1n0, float m1n1, float m1n2, float m1n3, float m2n0, float m2n1, float m2n2, float m2n3, float m3n0, float m3n1, float m3n2, float m3n3)
{
	m_d[0] = Vec4(m0n0, m0n1, m0n2, m0n3);
	m_d[1] = Vec4(m1n0, m1n1, m1n2, m1n3);
	m_d[2] = Vec4(m2n0, m2n1, m2n2, m2n3);
	m_d[3] = Vec4(m3n0, m3n1, m3n2, m3n3);
}

Matrix4x4::Matrix4x4(const Vec4 &m0, const Vec4 &m1, const Vec4 &m2, const Vec4 &m3)
{
	m_d[0] = m0;
	m_d[1] = m1;
	m_d[2] = m2;
	m_d[3] = m3;
}

Matrix4x4::Matrix4x4(float *data)
{
	m_d[0][0] = data[0]; m_d[0][1] = data[1]; m_d[0][2] = data[2]; m_d[0][3] = data[3];
	m_d[1][0] = data[4]; m_d[1][1] = data[5]; m_d[1][2] = data[6]; m_d[1][3] = data[7];
	m_d[2][0] = data[8]; m_d[2][1] = data[9]; m_d[2][2] = data[10]; m_d[2][3] = data[11];
	m_d[3][0] = data[12]; m_d[3][1] = data[13]; m_d[3][2] = data[14]; m_d[3][3] = data[15];
}

Matrix4x4::Matrix4x4(float *data, uint32_t count)
{
	if (count > size())	count = size();
	memcpy(this->data(), data, count * sizeof(float));
}

Matrix4x4 Matrix4x4::identity()
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::translateMatrix(float x, float y, float z)
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f);
}

Matrix4x4 Matrix4x4::scaleMatrix(float x, float y, float z)
{
	return Matrix4x4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4::Matrix4x4(const Matrix4x4 & other)
{
	*this = other;
}

void Matrix4x4::operator=(const Matrix4x4 & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
	m_d[2] = other.m_d[2];
	m_d[3] = other.m_d[3];
}

bool Matrix4x4::operator==(const Matrix4x4 & other) const
{
	return !operator!=(other);
}

bool Matrix4x4::operator!=(const Matrix4x4 & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1] || m_d[2] != other.m_d[2] || m_d[3] != other.m_d[3];
}

Vec4 & Matrix4x4::operator[](uint32_t row)
{
	if (row >= this->row())
		NB_THROW_EXCEPTION(std::out_of_range, "row[%d] is out of range [%d, %d)", row, 0, this->row());

	return m_d[row];
}

const Vec4 & Matrix4x4::operator[](uint32_t row) const
{
	return const_cast<Matrix4x4 *>(this)->operator[](row);
}

Matrix4x4 Matrix4x4::operator + (float f) const
{
	return Matrix4x4(m_d[0] + f, m_d[1] + f, m_d[2] + f, m_d[3] + f);
}

Matrix4x4 Matrix4x4::operator + (const Matrix4x4 &other) const
{
	return Matrix4x4(m_d[0] + other.m_d[0], m_d[1] + other.m_d[1], m_d[2] + other.m_d[2], m_d[3] + other.m_d[3]);
}

Matrix4x4 Matrix4x4::operator - (float f) const
{
	return Matrix4x4(m_d[0] - f, m_d[1] - f, m_d[2] - f, m_d[3] - f);
}

Matrix4x4 Matrix4x4::operator - (const Matrix4x4 &other) const
{
	return Matrix4x4(m_d[0] - other.m_d[0], m_d[1] - other.m_d[1], m_d[2] - other.m_d[2], m_d[3] - other.m_d[3]);
}

Matrix4x4 Matrix4x4::operator * (float f) const
{
	return Matrix4x4(m_d[0] * f, m_d[1] * f, m_d[2] * f, m_d[3] * f);
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4 &right) const
{
	Matrix4x4 ret;
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

Matrix4x4 Matrix4x4::operator/(float f) const
{
	return Matrix4x4(m_d[0] / f, m_d[1] / f, m_d[2] / f, m_d[3] / f);
}

float * Matrix4x4::data()
{
	return m_d[0].data();
}

const float * Matrix4x4::data() const
{
	return m_d[0].data();
}

uint32_t Matrix4x4::size() const
{
	return 16;
}

uint32_t Matrix4x4::row() const
{
	return 4;
}

uint32_t Matrix4x4::column() const
{
	return 4;
}

float & Matrix4x4::at(uint32_t row, uint32_t col)
{
	return (*this)[row][col];
}

const float & Matrix4x4::at(uint32_t row, uint32_t col) const
{
	return (*this)[row][col];
}

bool Matrix4x4::isIdentity() const
{
	return *this == identity();
}

void Matrix4x4::toIdentity()
{
	*this = identity();
}

Matrix4x4 &Matrix4x4::translate(float x, float y, float z)
{
	*this = translateMatrix(x, y, z) * (*this);
	return *this;
}

Matrix4x4 &Matrix4x4::translateX(float x)
{
	return translate(x, 0.0f, 0.0f);
}

Matrix4x4 &Matrix4x4::translateY(float y)
{
	return translate(0.0f, y, 0.0f);
}

Matrix4x4 &Matrix4x4::translateZ(float z)
{
	return translate(0.0f, 0.0f, z);
}

Matrix4x4 &Matrix4x4::rotateRadian(float radian, float x, float y, float z)
{
	float s = sin(radian);
	float c = cos(radian);
	*this = Matrix4x4(
		c + pow(x, 2) * (1 - c), x * y * (1 - c) - z * s, x * z * (1 - c) + y * s, 0,
		y * x * (1 - c) + z * s, c + pow(y, 2) * (1 - c), y * z * (1 - c) - x * s, 0,
		z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + pow(z, 2) * (1 - c), 0,
		0, 0, 0, 1) * (*this);
	return *this;
}

Matrix4x4 &Matrix4x4::rotateRadianX(float radian)
{
	return rotateRadian(radian, 1.0f, 0.0f, 0.0f);
}

Matrix4x4 &Matrix4x4::rotateRadianY(float radian)
{
	return rotateRadian(radian, 0.0f, 1.0f, 0.0f);
}

Matrix4x4 &Matrix4x4::rotateRadianZ(float radian)
{
	return rotateRadian(radian, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 &Matrix4x4::rotateAngle(float angle, float x, float y, float z)
{
	auto radian = NB_ANG2RAD(angle);
	return rotateRadian((float)radian, x, y, z);
}

Matrix4x4 &Matrix4x4::rotateAngleX(float angle)
{
	return rotateAngle(angle, 1.0f, 0.0f, 0.0f);
}

Matrix4x4 &Matrix4x4::rotateAngleY(float angle)
{
	return rotateAngle(angle, 0.0f, 1.0f, 0.0f);
}

Matrix4x4 &Matrix4x4::rotateAngleZ(float angle)
{
	return rotateAngle(angle, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 &Matrix4x4::scale(float x, float y, float z)
{
	*this = Matrix4x4::scaleMatrix(x, y, z) * (*this);
	return *this;
}

Matrix4x4 &Matrix4x4::scaleX(float x)
{
	return scale(x, 1.0f, 1.0f);
}

Matrix4x4 &Matrix4x4::scaleY(float y)
{
	return scale(1.0f, y, 1.0f);
}

Matrix4x4 &Matrix4x4::scaleZ(float z)
{
	return scale(1.0f, 1.0f, z);
}

Matrix4x4 &Matrix4x4::scaleUniform(float uniform)
{
	return scale(uniform, uniform, uniform);
}
