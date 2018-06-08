/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-04

* 简要描述:  与IO相关的异常

* 修改记录:

*****************************************************************************/
#include <string>
#include "core/Exception.h"

namespace nb{ namespace System{

class NB_EXPORT IOException : public nb::Core::Exception
{
public:
	IOException();
	IOException(const char *ioName);
	IOException(const char *ioName, const char *message);

	const char *GetName();

private:
	std::string		m_Name;
};
typedef nbObjectPtrDerive<IOException, nb::Core::ExceptionPtr>	IOExceptionPtr;

//未找到目录异常
class NB_EXPORT FileNotFoundException : public IOException
{
public:
	FileNotFoundException();
	FileNotFoundException(const char *ioName);
	FileNotFoundException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<FileNotFoundException, IOExceptionPtr>	FileNotFoundExceptionPtr;

//未找到文件异常
class NB_EXPORT DirectoryNotFoundException : public IOException
{
public:
	DirectoryNotFoundException();
	DirectoryNotFoundException(const char *ioName);
	DirectoryNotFoundException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<DirectoryNotFoundException, IOExceptionPtr>	DirectoryNotFoundExceptionPtr;

//文件流已到达末尾异常
class NB_EXPORT EndOfStreamException : public IOException
{
public:
	EndOfStreamException();
	EndOfStreamException(const char *ioName);
	EndOfStreamException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<EndOfStreamException, IOExceptionPtr>	EndOfStreamExceptionPtr;

//文件加载失败异常
class NB_EXPORT FileLoadFailedException : public IOException
{
public:
	FileLoadFailedException();
	FileLoadFailedException(const char *ioName);
	FileLoadFailedException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<FileLoadFailedException, IOExceptionPtr>	FileLoadFailedExceptionPtr;

//文件名太长异常
class NB_EXPORT PathTooLongException : public IOException
{
public:
	PathTooLongException();
	PathTooLongException(const char *ioName);
	PathTooLongException(const char *ioName, const char *message);

};
typedef nbObjectPtrDerive<PathTooLongException, IOExceptionPtr>	PathTooLongExceptionPtr;


}}
