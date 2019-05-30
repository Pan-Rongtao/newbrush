#include "core/Matrix2x2.h"
#include <exception>
#include <cstring>

using namespace nb::core;

Matrix2x2::Matrix2x2()
{
}

Matrix2x2::Matrix2x2(float m0n0, float m0n1, float m1n0, float m1n1)
{
	m_d[0] = Vec2(m0n0, m0n1);
	m_d[1] = Vec2(m1n0, m1n1);
}

Matrix2x2::Matrix2x2(const Vec2 &m0, const Vec2 &m1)
{
	m_d[0] = m0;
	m_d[1] = m1;
}

Matrix2x2::Matrix2x2(float *data)
{
	m_d[0][0] = data[0]; m_d[0][1] = data[1];
	m_d[1][0] = data[2]; m_d[1][1] = data[3];
}

Matrix2x2::Matrix2x2(float *data, uint32_t count)
{
	if (count > size())	count = size();
	memcpy(this->data(), data, count * sizeof(float));
}

Matrix2x2 Matrix2x2::identity()
{
	return Matrix2x2(1.0f, 0.0f, 0.0f, 1.0f);
}

Matrix2x2::Matrix2x2(const Matrix2x2 & other)
{
	*this = other;
}

void Matrix2x2::operator=(const Matrix2x2 & other)
{
	m_d[0] = other.m_d[0];
	m_d[1] = other.m_d[1];
}

bool Matrix2x2::operator==(const Matrix2x2 & other) const
{
	return !(operator!=(other));
}

bool Matrix2x2::operator!=(const Matrix2x2 & other) const
{
	return m_d[0] != other.m_d[0] || m_d[1] != other.m_d[1];
}

Vec2 & Matrix2x2::operator[](uint32_t row)
{
	if (row >= this->row())
		NB_THROW_EXCEPTION(std::out_of_range, "row[%d] is out of range [0, %d)", row, this->row());

	return m_d[row];
}

const Vec2 & Matrix2x2::operator[](uint32_t row) const
{
	return const_cast<Matrix2x2 *>(this)->operator[](row);
}

Matrix2x2 Matrix2x2::operator + (float f) const
{
	return Matrix2x2(m_d[0] + f, m_d[1] + f);
}

Matrix2x2 Matrix2x2::operator + (const Matrix2x2 &other) const
{
	return Matrix2x2(m_d[0] + other.m_d[0], m_d[1] + other.m_d[1]);
}

Matrix2x2 Matrix2x2::operator - (float f) const
{
	return Matrix2x2(m_d[0] - f, m_d[1] - f);
}

Matrix2x2 Matrix2x2::operator - (const Matrix2x2 &other) const
{
	return Matrix2x2(m_d[0] - other.m_d[0], m_d[1] - other.m_d[1]);
}

Matrix2x2 Matrix2x2::operator * (float f) const
{
	return Matrix2x2(m_d[0] * f, m_d[1] * f);
}

Matrix2x2 Matrix2x2::operator * (const Matrix2x2 &right) const
{
	Matrix2x2 ret;
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

Matrix2x2 Matrix2x2::operator/(float f) const
{
	return Matrix2x2(m_d[0] / f, m_d[1] / f);
}

float * Matrix2x2::data()
{
	return m_d[0].data();
}

const float * Matrix2x2::data() const
{
	return m_d[0].data();
}

uint32_t Matrix2x2::size() const
{
	return 4;
}

uint32_t Matrix2x2::row() const
{
	return 2;
}

uint32_t Matrix2x2::column() const
{
	return 2;
}

float & Matrix2x2::at(uint32_t row, uint32_t col)
{
	return (*this)[row][col];
}

const float & Matrix2x2::at(uint32_t row, uint32_t col) const
{
	return (*this)[row][col];
}

bool Matrix2x2::isIdentity() const
{
	return *this == identity();
}

void Matrix2x2::toIdentity()
{
	*this = identity();
}
