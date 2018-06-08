#include "system/IOException.h"

using nb::Core::Exception;
using nb::System::IOException;
using nb::System::FileNotFoundException;
using nb::System::DirectoryNotFoundException;
using nb::System::EndOfStreamException;
using nb::System::FileLoadFailedException;
using nb::System::PathTooLongException;

IOException::IOException()
{
}

IOException::IOException(const char *ioName)
: m_Name(ioName)
{
}

IOException::IOException(const char *ioName, const char *message)
: Exception(message)
, m_Name(ioName)
{
}

const char *IOException::GetName()
{
	return m_Name.data();
}

/////////
FileNotFoundException::FileNotFoundException()
{
}

FileNotFoundException::FileNotFoundException(const char *ioName)
: IOException(ioName)
{
}

FileNotFoundException::FileNotFoundException(const char *ioName, const char *message)
: IOException(ioName, message)
{
}

//////////////
DirectoryNotFoundException::DirectoryNotFoundException()
{
}

DirectoryNotFoundException::DirectoryNotFoundException(const char *ioName)
: IOException(ioName)
{
}

DirectoryNotFoundException::DirectoryNotFoundException(const char *ioName, const char *message)
: IOException(ioName, message)
{
}

//////////////
EndOfStreamException::EndOfStreamException()
{
}

EndOfStreamException::EndOfStreamException(const char *ioName)
: IOException(ioName)
{
}

EndOfStreamException::EndOfStreamException(const char *ioName, const char *message)
: IOException(ioName, message)
{
}

//////////////
FileLoadFailedException::FileLoadFailedException()
{
}

FileLoadFailedException::FileLoadFailedException(const char *ioName)
: IOException(ioName)
{
}

FileLoadFailedException::FileLoadFailedException(const char *ioName, const char *message)
: IOException(ioName, message)
{
}

//////////////////////
PathTooLongException::PathTooLongException()
{
}

PathTooLongException::PathTooLongException(const char *ioName)
: IOException(ioName)
{
}

PathTooLongException::PathTooLongException(const char *ioName, const char *message)
: IOException(ioName, message)
{
}
