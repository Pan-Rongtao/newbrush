#include "system/ArgumentException.h"

using nb::Core::Exception;
using nb::System::ArgumentException;
using nb::System::ArgumentNullException;
using nb::System::ArgumentOutOfRangeException;

ArgumentException::ArgumentException(const char *paramName)
: m_ParamName(paramName)
{
}

ArgumentException::ArgumentException(const char *paramName, const char *message)
: Exception(message)
, m_ParamName(paramName)
{
}

const char *ArgumentException::GetParamName() const
{
	return m_ParamName.data();
}

///////////////
ArgumentNullException::ArgumentNullException(const char *paramName)
: ArgumentException(paramName)
{
}

ArgumentNullException::ArgumentNullException(const char *paramName, const char *message)
: ArgumentException(paramName, message)
{
}

///////////////
ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char *paramName, void *v, void *lowBound, void *upBound)
: ArgumentException(paramName)
, m_LowBound(lowBound)
, m_UpBound(upBound)
{
}

ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char *paramName, void *v, void *lowBound, void *upBound, const char *message)
: ArgumentException(paramName, message)
, m_LowBound(lowBound)
, m_UpBound(upBound)
{
}

void *ArgumentOutOfRangeException::GetLowBound() const
{
	return m_LowBound;
}

void *ArgumentOutOfRangeException::GetUpBound() const
{
	return m_UpBound;
}

void *ArgumentOutOfRangeException::GetValue() const
{
	return m_V;
}
