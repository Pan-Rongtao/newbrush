#include "math/Vec.h"
#include "core/Exception.h"
#include "system/System.h"

using nb::Math::Vec;

Vec::Vec(int dimension)
: m_Data(NULL)
{
	if(dimension <= 0)
	{
		m_Dimension = 0;
		NB_THROW_EXCEPTION("dimension <= 0");
	}

	m_Dimension = dimension;
	m_Data = new float[m_Dimension];
	memset(m_Data, 0, m_Dimension * sizeof(float));
}

Vec::Vec(const Vec &other)
{
	m_Dimension = other.m_Dimension;
	m_Data = new float[m_Dimension];
	memcpy(m_Data, other.m_Data, sizeof(float) * m_Dimension);
}

Vec::~Vec()
{
	delete [] m_Data;
}

Vec & Vec::operator = (const Vec &other)
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	memcpy(m_Data, other.m_Data, sizeof(float) * m_Dimension);
	return *this;
}

int Vec::GetDimension() const
{
	return m_Dimension;
}

float &Vec::At(int index)
{
	if(index < 0 || index >= GetDimension())
		NB_THROW_EXCEPTION("index over flow");

	return m_Data[index];
}

const float &Vec::At(int index) const
{
	if(index < 0 || index >= GetDimension())
		NB_THROW_EXCEPTION("index over flow");

	return m_Data[index];
}

float Vec::Norm() const
{
	float fSum = 0.0;
	for(int i = 0;i != GetDimension(); ++i)
		fSum += (At(i) * At(i));

	return (float)nb::System::Sqrt(fSum);
}

float Vec::Lenght() const
{
	return Norm();
}

Vec Vec::Normalized() const
{
	Vec ret(*this);
	for(int i = 0; i != GetDimension(); ++i)
		ret[i] /= Norm();
	return ret;
}

const float *Vec::GetData() const
{
	return m_Data;
}

float *Vec::GetData()
{
	return m_Data;
}

float Vec::DotProduct(const Vec &other) const
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	float ret = 0;
	for(int i = 0; i != m_Dimension; ++i)
		ret += At(i) * other.At(i);
	return ret;
}

bool Vec::operator == (const Vec &other) const
{
	return (m_Dimension == other.m_Dimension) && (memcmp(m_Data, other.m_Data, sizeof(float) * m_Dimension) == 0);
}

bool Vec::operator != (const Vec &other) const
{
	return !(operator == (other));
}

float &Vec::operator [] (int index)
{
	return At(index);
}

const float &Vec::operator [] (int index) const
{
	return At(index);
}

Vec Vec::operator + (float f) const
{
	Vec ret(*this);
	ret += f;
	return ret;
}

Vec Vec::operator + (const Vec &v) const
{
	Vec	ret(*this);
	ret += v;
	return ret;
}

Vec Vec::operator - (float f) const
{
	Vec ret(*this);
	ret -= f;
	return ret;
}

Vec Vec::operator - (const Vec &v) const
{
	Vec ret(*this);
	ret -= v;
	return ret;
}

Vec Vec::operator * (float f) const
{
	Vec ret(*this);
	ret *= f;
	return ret;
}

Vec Vec::operator / (float f) const
{
	Vec ret(*this);
	ret /= f;
	return ret;
}

void Vec::operator += (float f)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] += f;
}

void Vec::operator += (const Vec &other)
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] += other.m_Data[i];
}

void Vec::operator -= (float f)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] -= f;
}

void Vec::operator -= (const Vec &other)
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] -= other.m_Data[i];
}

void Vec::operator *= (float f)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] *= f;
}

void Vec::operator /= (float f)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] /= f;
}

Vec Vec::operator - () const
{
	Vec ret = *this;
	for(int i = 0; i != m_Dimension; ++i)
		ret[i] = -ret[i];
	return ret;
}
