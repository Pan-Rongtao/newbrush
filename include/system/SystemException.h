/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-04

* 简要描述:  系统相关的异常

* 修改记录:

*****************************************************************************/
#include "core/Exception.h"

namespace nb{ namespace System{

//系统异常基类
class NB_EXPORT SystemException : public nb::Core::Exception
{
public:
	SystemException();
	SystemException(const char *message);
};
typedef nbObjectPtrDerive<SystemException, nb::Core::ExceptionPtr>	SystemExceptionPtr;

//逻辑错误
class NB_EXPORT LogicException : public SystemException
{
public:
	LogicException();
	LogicException(const char *message);

};
typedef nbObjectPtrDerive<LogicException, SystemExceptionPtr>	LogicExceptionPtr;

//错误的调用时序
class NB_EXPORT BadTimingOperationException : public LogicException
{
public:
	BadTimingOperationException();
	BadTimingOperationException(const char *message);

};
typedef nbObjectPtrDerive<BadTimingOperationException, LogicExceptionPtr>	BadTimingOperationExceptionPtr;

}}