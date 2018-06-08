#include "system/SystemException.h"
#include "core/Exception.h"

using nb::Core::Exception;
using nb::System::SystemException;
using nb::System::LogicException;
using nb::System::BadTimingOperationException;

SystemException::SystemException()
{

}

SystemException::SystemException(const char *message)
: Exception(message)
{


}

LogicException::LogicException()
{

}

LogicException::LogicException(const char *message)
: SystemException(message)
{

}

BadTimingOperationException::BadTimingOperationException()
{

}

BadTimingOperationException::BadTimingOperationException(const char *message)
: LogicException(message)
{

}