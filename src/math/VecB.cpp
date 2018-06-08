#include "math/VecB.h"
#include "core/Exception.h"
#include "system/System.h"

using nb::Math::VecB;

VecB::VecB(int dimension)
: m_Data(NULL)
{
	if(dimension <= 0)
	{
		m_Dimension = 0;
		NB_THROW_EXCEPTION("dimension <= 0");
	}

	m_Dimension = dimension;
	m_Data = new bool[m_Dimension];
	memset(m_Data, 0, m_Dimension * sizeof(bool));
}

VecB::VecB(const VecB &other)
{
	m_Dimension = other.m_Dimension;
	m_Data = new bool[m_Dimension];
	memcpy(m_Data, other.m_Data, sizeof(bool) * m_Dimension);
}

VecB::~VecB()
{
	delete [] m_Data;
}

VecB &VecB::operator = (const VecB &other)
{
	if(GetDimension() != other.m_Dimension)
		NB_THROW_EXCEPTION("dimension is not same");

	memcpy(m_Data, other.m_Data, sizeof(bool) * m_Dimension);
	return *this;
}

int VecB::GetDimension() const
{
	return m_Dimension;
}

bool &VecB::At(int index)
{
	if(index < 0 || index >= GetDimension())
		NB_THROW_EXCEPTION("index over flow");

	return m_Data[index];
}

const bool &VecB::At(int index) const
{
	if(index < 0 || index >= GetDimension())
		NB_THROW_EXCEPTION("index over flow");

	return m_Data[index];
}

float VecB::Norm() const
{
	return (float)nb::System::Sqrt(GetDimension());
}

float VecB::Lenght() const
{
	return Norm();
}

const bool *VecB::GetData() const
{
	return m_Data;
}

bool *VecB::GetData()
{
	return m_Data;
}

bool VecB::operator == (const VecB &other) const
{
	return (m_Dimension == other.m_Dimension) && (memcmp(m_Data, other.m_Data, sizeof(bool) * m_Dimension) == 0);
}

bool VecB::operator != (const VecB &other) const
{
	return !(operator == (other));
}

bool & VecB::operator [] (int index)
{
	return At(index);
}

const bool & VecB::operator [] (int index) const
{
	return At(index);
}
