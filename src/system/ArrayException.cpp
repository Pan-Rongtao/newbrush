#include "system/ArrayException.h"

using nb::Core::Exception;
using nb::System::ArrayException;
using nb::System::ArrayIndexOutOfRangeException;
using nb::System::ArrayRankException;


ArrayException::ArrayException()
{
}

ArrayException::ArrayException(const char *message)
: Exception(message)
{
}

//////////////
ArrayIndexOutOfRangeException::ArrayIndexOutOfRangeException(int arraySize, int index)
: m_ArraySize(arraySize)
, m_Index(index)
{
}

ArrayIndexOutOfRangeException::ArrayIndexOutOfRangeException(int arraySize, int index, const char *message)
: ArrayException(message)
, m_ArraySize(arraySize)
, m_Index(index)
{
}

//////////////
ArrayRankException::ArrayRankException()
{
}

ArrayRankException::ArrayRankException(const char *message)
: ArrayException(message)
{
}
