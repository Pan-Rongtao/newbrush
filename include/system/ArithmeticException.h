/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-04

* 简要描述:  算术相关的异常

* 修改记录:

*****************************************************************************/
#include "core/Exception.h"

namespace nb{ namespace System{

class NB_EXPORT ArithmeticException : public nb::Core::Exception
{
public:
	ArithmeticException();
	ArithmeticException(const char *message);
};
typedef nbObjectPtrDerive<ArithmeticException, nb::Core::ExceptionPtr>	ArithmeticExceptionPtr;

//十进制运算中试图除以零而引发的异常
class NB_EXPORT DivideByZeroException : public ArithmeticException
{
public:
	DivideByZeroException();
	DivideByZeroException(const char *message);

};
typedef nbObjectPtrDerive<DivideByZeroException, ArithmeticExceptionPtr>	DivideByZeroExceptionPtr;

}}
