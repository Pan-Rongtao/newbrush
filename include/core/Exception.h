#pragma once
#include <string>
#include "../core/Def.h"
#include "../core/Any.h"
#include <exception>

namespace nb { namespace core {

class NB_API Exception
{
public:
	Exception(const std::string &file = "", int line = -1);
	Exception(const char *msg, const std::string &file = "", int line = -1);
	virtual ~Exception();

	std::string file() const;
	int line() const;
	
	virtual std::string what() const;

protected:
	std::string messageHeader() const;

private:
	std::string		m_msg;
	std::string		m_file;
	int				m_line;
};

//参数异常
class NB_API ArgumentException : public nb::core::Exception
{
public:
	ArgumentException(const char *paramName, const std::string &file = "", int line = -1);
	const char *paramName() const;
	virtual std::string what() const override;

protected:
	std::string		m_paramName;
};

//空传递给不接受它作为有效参数的方法时引发的异常
class NB_API ArgumentNullException : public ArgumentException
{
public:
	ArgumentNullException(const char *paramName, const std::string &file = "", int line = -1);
	virtual std::string what() const override;
};

//参数值超出调用的方法所定义的允许取值范围时引发的异常
class NB_API ArgumentOutOfRangeException : public ArgumentException
{
public:
	ArgumentOutOfRangeException(const char *paramName, const Any &lower, const Any &upper, const Any &value, const std::string &file = "", int line = -1);
	const Any &lower() const;
	const Any &upper() const;
	const Any &value() const;
	virtual std::string what() const;

private:
	Any		m_lower;
	Any		m_upper;
	Any		m_value;
};

///////////////////////////////
//算数异常
class NB_API ArithmeticException : public nb::core::Exception
{
public:
	ArithmeticException(const std::string &file = "", int line = -1);
	virtual std::string what() const;

};

//十进制运算中试图除以零而引发的异常
class NB_API DivideByZeroException : public ArithmeticException
{
public:
	DivideByZeroException(const std::string &file = "", int line = -1);
	virtual std::string what() const;
};

////////数组异常
class NB_API ArrayException : public nb::core::Exception
{
public:
	ArrayException(const std::string &file = "", int line = -1);
	virtual std::string what() const;
};

//索引超出数组界限的数组元素时引发的异常
class NB_API ArrayIndexOutOfRangeException : public ArrayException
{
public:
	ArrayIndexOutOfRangeException(int arraySize, int index, const std::string &file = "", int line = -1);
	int arraySize() const;
	int index() const;
	virtual std::string what() const;

private:
	int	m_size;
	int m_index;
};

//维数错误的数组传递给方法时引发的异常
class NB_API ArrayDimensionException : public ArrayException
{
public:
	ArrayDimensionException(int correctDimension, int illegalDimension, const std::string &file = "", int line = -1);
	int correctDimension() const;
	int illegalDimension() const;
	virtual std::string what() const;

private:
	int m_correct;
	int m_illegal;
};

//系统异常基类
class NB_API SystemException : public nb::core::Exception
{
public:
	SystemException(const std::string &file = "", int line = -1);
	virtual std::string what() const;
};

//逻辑错误
class NB_API LogicException : public SystemException
{
public:
	LogicException(const std::string &file = "", int line = -1);
	virtual std::string what() const;
};

//错误的调用时序
class NB_API BadTimingOperationException : public LogicException
{
public:
	BadTimingOperationException(const std::string &file = "", int line = -1);
	virtual std::string what() const;
};

//IO异常
class NB_API IOException : public Exception
{
public:
	IOException(const char *ioName, const std::string &file = "", int line = -1);
	const char *ioName() const;
	virtual std::string what() const;

private:
	std::string		m_ioName;
};

//未找到目录异常
class NB_API FileNotFoundException : public IOException
{
public:
	FileNotFoundException(const char *filePath, const std::string &file = "", int line = -1);
	virtual std::string what() const;
};

//未找到文件异常
class NB_API DirectoryNotFoundException : public IOException
{
public:
	DirectoryNotFoundException(const char *dir, const std::string &file = "", int line = -1);
	std::string what() const;
};

//文件流已到达末尾异常
class NB_API EndOfStreamException : public IOException
{
public:
	EndOfStreamException(const char *ioName, const std::string &file = "", int line = -1);
	std::string what() const;
};

//文件加载失败异常
class NB_API FileLoadFailedException : public IOException
{
public:
	FileLoadFailedException(const char *filePath, const std::string &file = "", int line = -1);
	std::string what() const;
};

//文件名太长异常
class NB_API PathTooLongException : public IOException
{
public:
	PathTooLongException(const char *path, int limit, const std::string &file = "", int line = -1);
	int limit() const;
	std::string what() const;

private:
	int		m_limit;
};


}}

