#include "math/VecI.h"
#include "core/Exception.h"
#include "system/System.h"

using nb::Math::VecI;

VecI::VecI(int dimension)
: m_Data(NULL)
{
	if(dimension <= 0)
	{
		m_Dimension = 0;
		NB_THROW_EXCEPTION("dimension <= 0");
	}

	m_Dimension = dimension;
	m_Data = new int[m_Dimension];
	memset(m_Data, 0, m_Dimension * sizeof(int));
}

VecI::VecI(const VecI &other)
{
	m_Dimension = other.m_Dimension;
	m_Data = new int[m_Dimension];
	memcpy(m_Data, other.m_Data, sizeof(int) * m_Dimension);
}

VecI::~VecI()
{
	delete [] m_Data;
}

VecI & VecI::operator = (const VecI &other)
{
	if(GetDimension() != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	memcpy(m_Data, other.m_Data, sizeof(int) * m_Dimension);
	return *this;
}

int VecI::GetDimension() const
{
	return m_Dimension;
}

int &VecI::At(int index)
{
	if(index < 0 || index >= GetDimension())
		NB_THROW_EXCEPTION("index over flow");

	return m_Data[index];
}

const int &VecI::At(int index) const
{
	if(index < 0 || index >= GetDimension())
		NB_THROW_EXCEPTION("index over flow");

	return m_Data[index];
}

float VecI::Norm() const
{
	float fSum = 0.0f;
	for(int i = 0;i != GetDimension(); ++i)
		fSum += (At(i) * At(i));

	return (float)nb::System::Sqrt(fSum);
}

float VecI::Lenght() const
{
	return Norm();
}

VecI VecI::Normalized()
{
	VecI ret(*this);
	for(int i = 0; i != GetDimension(); ++i)
		ret[i] /= Norm();
	return ret;
}

const int *VecI::GetData() const
{
	return m_Data;
}

int *VecI::GetData()
{
	return m_Data;
}

int VecI::DotProduct(const VecI &other) const
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	int ret = 0;
	for(int i = 0; i != m_Dimension; ++i)
		ret += At(i) * other.At(i);
	return ret;
}

bool VecI::operator == (const VecI &other) const
{
	return (m_Dimension == other.m_Dimension) && (memcmp(m_Data, other.m_Data, sizeof(int) * m_Dimension) == 0);
}

bool VecI::operator != (const VecI &other) const
{
	return !(operator == (other));
}

int & VecI::operator [] (int index)
{
	return At(index);
}

const int & VecI::operator [] (int index) const
{
	return At(index);
}

VecI VecI::operator + (int n) const
{
	VecI ret(*this);
	ret += n;
	return ret;
}

VecI VecI::operator + (const VecI &v) const
{
	VecI	ret(*this);
	ret += v;
	return ret;
}

VecI VecI::operator - (int n) const
{
	VecI ret(*this);
	ret -= n;
	return ret;
}

VecI VecI::operator - (const VecI &v) const
{
	VecI ret(*this);
	ret -= v;
	return ret;
}

VecI VecI::operator * (int n) const
{
	VecI ret(*this);
	ret *= n;
	return ret;
}

VecI VecI::operator / (int n) const
{
	VecI ret(*this);
	ret /= n;
	return ret;
}

void VecI::operator += (int n)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] += n;
}

void VecI::operator += (const VecI &other)
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] += other.m_Data[i];
}

void VecI::operator -= (int n)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] -= n;
}

void VecI::operator -= (const VecI &other)
{
	if(m_Dimension != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] -= other.m_Data[i];
}

void VecI::operator *= (int n)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] *= n;
}

void VecI::operator /= (int n)
{
	for(int i = 0; i != m_Dimension; ++i)
		m_Data[i] /= n;
}

VecI VecI::operator - () const
{
	VecI ret = *this;
	for(int i = 0; i != m_Dimension; ++i)
		ret[i] = -ret[i];
	return ret;
}
