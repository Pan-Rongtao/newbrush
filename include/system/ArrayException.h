/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-04

* 简要描述:  与数组相关的异常

* 修改记录:

*****************************************************************************/
#include "core/Exception.h"

namespace nb{ namespace System{

class NB_EXPORT ArrayException : public nb::Core::Exception
{
public:
	ArrayException();
	ArrayException(const char *message);
	
};
typedef nbObjectPtrDerive<ArrayException, nb::Core::ExceptionPtr>	ArrayExceptionPtr;

//索引超出数组界限的数组元素时引发的异常
class NB_EXPORT ArrayIndexOutOfRangeException : public ArrayException
{
public:
	ArrayIndexOutOfRangeException(int arraySize, int index);
	ArrayIndexOutOfRangeException(int arraySize, int index, const char *message);

private:
	int	m_ArraySize;
	int m_Index;
};
typedef nbObjectPtrDerive<ArrayIndexOutOfRangeException, ArrayExceptionPtr>	ArrayIndexOutOfRangeExceptionPtr;

//维数错误的数组传递给方法时引发的异常
class NB_EXPORT ArrayRankException : public ArrayException
{
public:
	ArrayRankException();
	ArrayRankException(const char *message);
};
typedef nbObjectPtrDerive<ArrayRankException, ArrayExceptionPtr>	ArrayRankExceptionPtr;

}}
