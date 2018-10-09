#include "core/Exception.h"

using namespace nb::core;

Exception::Exception(const std::string &file, int line)
	: m_file(file)
	, m_line(line)
{
}

Exception::Exception(const char *msg, const std::string &file, int line)
	: m_msg(msg)
	, m_file(file)
	, m_line(line)
{
}

Exception::~Exception()
{
}

std::string Exception::file() const
{
	return m_file;
}

int nb::core::Exception::line() const
{
	return m_line;
}

std::string Exception::what() const
{
	return m_msg.empty() ? messageHeader() + "undescribed." : messageHeader() + m_msg;
}

std::string Exception::messageHeader() const
{
	char arr[256] = { 0 };
	size_t n = std::string::npos;
	if (((n = m_file.rfind('/')) != std::string::npos) || ((n = m_file.rfind('\\')) != std::string::npos))
		snprintf(arr, sizeof(arr), "[file:%s,line:%d] throw an %s: ", m_file.substr(n + 1).data(), m_line, typeid(*this).name());
	else
		snprintf(arr, sizeof(arr), "[file:%s,line:%d] throw an %s:", m_file.data(), m_line, typeid(*this).name());
	return arr;
}

ArgumentException::ArgumentException(const char *paramName, const std::string &file, int line)
	: Exception(file, line)
	, m_paramName(paramName)
{
}

const char * ArgumentException::paramName() const
{
	return m_paramName.data();
}

std::string ArgumentException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "param[%s]", m_paramName.data());
	return messageHeader() + arr;
}

///////////////
ArgumentNullException::ArgumentNullException(const char *paramName, const std::string &file, int line)
	: ArgumentException(paramName, file, line)
{
}

std::string ArgumentNullException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "param[%s]", m_paramName.data());
	return messageHeader() + arr;
}

///////////////
ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char *paramName, const Any &lower, const Any &upper, const Any &value, const std::string &file, int line)
	: ArgumentException(paramName, file, line)
	, m_lower(lower)
	, m_upper(upper)
	, m_value(value)
{
}

const Any &ArgumentOutOfRangeException::lower() const
{ 
	return m_lower; 
}

const Any &ArgumentOutOfRangeException::upper() const
{ 
	return m_upper; 
}

const Any &ArgumentOutOfRangeException::value() const
{ 
	return m_value;
}

std::string ArgumentOutOfRangeException::what() const
{
	char arr[256] = { 0 };
	if (m_value.type() == typeid(int8_t) || m_value.type() == typeid(uint8_t) || m_value.type() == typeid(int16_t) || m_value.type() == typeid(uint16_t)
		|| m_value.type() == typeid(int32_t) || m_value.type() == typeid(uint32_t) || m_value.type() == typeid(int64_t) || m_value.type() == typeid(uint64_t))
		snprintf(arr, sizeof(arr), "param [%s]'s value [%d] is out of [%d, %d]", m_paramName.data(), any_cast<int>(m_value), any_cast<int>(m_lower), any_cast<int>(m_upper));
	else if (m_value.type() == typeid(float) || m_value.type() == typeid(double))
		snprintf(arr, sizeof(arr), "param [%s]'s value [%.5f] is out of [%.5f, %.5f]", m_paramName.data(), any_cast<float>(m_value), any_cast<float>(m_lower), any_cast<float>(m_upper));
	return messageHeader() + arr;
}
///////////////////////////
ArithmeticException::ArithmeticException(const std::string &file, int line)
	: Exception(file, line)
{
}

std::string ArithmeticException::what() const
{
	return messageHeader() + "";
}

DivideByZeroException::DivideByZeroException(const std::string &file, int line)
	: ArithmeticException(file, line)
{
}

std::string DivideByZeroException::what() const
{
	return messageHeader() + "";
}

///////////////////////////////
ArrayException::ArrayException(const std::string &file, int line)
	: Exception(file, line)
{
}

std::string ArrayException::what() const
{
	return messageHeader() + "";
}
//////////////
ArrayIndexOutOfRangeException::ArrayIndexOutOfRangeException(int arraySize, int index, const std::string &file, int line)
	: ArrayException(file, line)
	, m_size(arraySize)
	, m_index(index)
{
}

int ArrayIndexOutOfRangeException::arraySize() const
{
	return m_size;
}

int ArrayIndexOutOfRangeException::index() const
{
	return m_index;
}

std::string ArrayIndexOutOfRangeException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "arraySize[%d], index[%d]", m_size, m_index);
	return messageHeader() + arr;
}

//////////////
ArrayDimensionException::ArrayDimensionException(int correctDimension, int illegalDimension, const std::string &file, int line)
	: ArrayException(file, line)
	, m_correct(correctDimension)
	, m_illegal(illegalDimension)
{
}

int ArrayDimensionException::correctDimension() const
{
	return m_correct;
}

int ArrayDimensionException::illegalDimension() const
{
	return m_illegal;
}

std::string ArrayDimensionException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "correct dimension[%d], illegal dimension[%d]", m_correct, m_illegal);
	return messageHeader() + arr;
}

/////////////////////////////
SystemException::SystemException(const std::string &file, int line)
	: Exception(file, line)
{

}

std::string SystemException::what() const
{
	return messageHeader() + "";
}

LogicException::LogicException(const std::string &file, int line)
	: SystemException(file, line)
{
}

std::string LogicException::what() const
{
	return messageHeader() + "";
}

BadTimingOperationException::BadTimingOperationException(const std::string &file, int line)
	: LogicException(file, line)
{
}

std::string BadTimingOperationException::what() const
{
	return messageHeader() + "";
}

/////////////////
IOException::IOException(const char *ioName, const std::string &file, int line)
	: Exception(file, line)
	, m_ioName(ioName)
{
}

const char *IOException::ioName() const
{
	return m_ioName.data();
}

std::string IOException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "io[%s]", ioName());
	return messageHeader() + arr;
}

/////////
FileNotFoundException::FileNotFoundException(const char *filePath, const std::string &file, int line)
	: IOException(filePath ,file, line)
{
}

std::string FileNotFoundException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "file[%s]", ioName());
	return messageHeader() + arr;
}
//////////////
DirectoryNotFoundException::DirectoryNotFoundException(const char *dir, const std::string &file, int line)
	: IOException(dir, file, line)
{
}

std::string DirectoryNotFoundException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "dir[%s]", ioName());
	return messageHeader() + arr;
}
//////////////
EndOfStreamException::EndOfStreamException(const char *ioName, const std::string &file, int line)
	: IOException(ioName, file, line)
{
}

std::string EndOfStreamException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "io[%s]", ioName());
	return messageHeader() + arr;
}
//////////////
FileLoadFailedException::FileLoadFailedException(const char *filePath, const std::string &file, int line)
	: IOException(filePath, file, line)
{
}

std::string FileLoadFailedException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "file[%s]", ioName());
	return messageHeader() + arr;
}
//////////////////////
PathTooLongException::PathTooLongException(const char *ioName, int limit, const std::string &file, int line)
	: IOException(ioName, file, line)
	, m_limit(limit)
{
}

int PathTooLongException::limit() const
{
	return m_limit;
}

std::string PathTooLongException::what() const
{
	char arr[256] = { 0 };
	snprintf(arr, sizeof(arr), "path[%s], limit by[%d]", ioName(), m_limit);
	return messageHeader() + arr;
}
