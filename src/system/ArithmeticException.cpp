#include "system/ArithmeticException.h"

using nb::Core::Exception;
using nb::System::ArithmeticException;
using nb::System::DivideByZeroException;

ArithmeticException::ArithmeticException()
{

}

ArithmeticException::ArithmeticException(const char *message)
: Exception(message)
{

}

DivideByZeroException::DivideByZeroException()
{

}

DivideByZeroException::DivideByZeroException(const char *message)
: ArithmeticException(message)
{

}
