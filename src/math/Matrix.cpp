#include "math/Matrix.h"
#include "core/Exception.h"

using nb::Math::Matrix;

Matrix::Matrix(unsigned int col, unsigned int row)
: m_col(col)
, m_row(row)
{
	m_Data = new float[m_col * m_row];
	memset(m_Data, 0, m_col * m_row * sizeof(float));
}

Matrix::Matrix(unsigned int col, unsigned int row, float *data)
: m_col(col)
, m_row(row)
{
	m_Data = new float[m_col * m_row];
	memcpy(m_Data, data, m_col * m_row * sizeof(float));
}

Matrix::Matrix(unsigned int col, unsigned int row, float *data, unsigned int count)
: m_col(col)
, m_row(row)
{
	m_Data = new float[m_col * m_row];
	memcpy(m_Data, data, m_col * m_row * sizeof(float));
	if(m_col * m_row <= count)
		memset(m_Data + count, 0, (m_col * m_row - count) * sizeof(float));
}

Matrix::Matrix(const Matrix &other)
{
	m_col = other.m_col;
	m_row = other.m_row;
	m_Data = new float[m_col * m_row];
	memcpy(m_Data, other.m_Data, m_col * m_row * sizeof(float));
}

Matrix::~Matrix()
{
	delete m_Data;
}

unsigned int Matrix::GetColumn() const
{
	return m_col;
}

unsigned int Matrix::GetRow() const
{
	return m_row;
}

const float &Matrix::At(unsigned int col, unsigned int row) const
{
	if(col >= GetColumn() || row >= GetRow())
		NB_THROW_EXCEPTION("invalid index");

	return m_Data[col * GetRow() + row];
}

float &Matrix::At(unsigned int col, unsigned int row)
{
	if(col >= GetColumn() || row >= GetRow())
		NB_THROW_EXCEPTION("invalid index");

	return m_Data[col * GetRow() + row];
}

const float *Matrix::GetData() const
{
	return m_Data;
}

float *Matrix::GetData()
{
	return m_Data;
}

Matrix & Matrix::operator = (const Matrix &other)
{
	if(GetColumn() != other.GetColumn() || GetRow() != other.GetRow())
		NB_THROW_EXCEPTION("not same type matrix");

	memcpy(m_Data, other.GetData(), GetColumn() * GetRow() * sizeof(float));
	return *this;
}

bool Matrix::operator == (const Matrix &other) const
{
	return (GetColumn() == other.GetColumn() && GetRow() == other.GetRow()) && memcmp(m_Data, other.m_Data, GetColumn() * GetRow() * sizeof(float) == 0);
}

bool Matrix::operator != (const Matrix &other) const
{
	return !(operator == (other));
}
/*
const float & Matrix::operator [] (unsigned int index) const
{
	if(index < 0 || index >= GetMDimension() * GetNDimension())
		NB_THROW_EXCEPTION("invalid index");

	return m_Data[index];
}

float & Matrix::operator [] (unsigned int index)
{
	if(index < 0 || index >= GetMDimension() * GetNDimension())
		NB_THROW_EXCEPTION("invalid index");

	return m_Data[index];
}
*/
bool Matrix::IsIdentity() const
{
	if(GetColumn() != GetRow())
		return false;

	for(unsigned int col = 0; col != GetColumn(); ++col)
	{
		for(unsigned int row = 0; row != GetRow(); ++row)
		{
			float v = At(col, row);
			if((col == row && v != 1.0f) || (col != row && v != 0.0f))
				return false;
		}
	}
	return true;
}

Matrix Matrix::operator * (const Matrix &other) const
{
	if(!Matrix::CanMultiply(*this, other))
		NB_THROW_EXCEPTION("can not nultiply");

	Matrix ret(GetColumn(), other.GetRow());
	for(unsigned int i = 0; i != ret.GetColumn(); ++i)
	{
		for(unsigned int j = 0; j != ret.GetRow(); ++j)
		{
			for(unsigned int k = 0; k != ret.GetRow(); ++k)
				ret.At(i, j) += At(i, k) * other.At(k, j);
		}
	}
	return ret;
}

bool Matrix::CanMultiply(const Matrix &matrix1, const Matrix &matrix2)
{
	return matrix1.GetColumn() == matrix2.GetRow();
}
