/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-04

* 简要描述:  参数相关的异常

* 修改记录:

*****************************************************************************/
#include <string>
#include "core/Exception.h"

namespace nb{ namespace System{

//参数异常
class NB_EXPORT ArgumentException : public nb::Core::Exception
{
public:
	ArgumentException(const char *paramName);
	ArgumentException(const char *paramName, const char *message);

	const char *GetParamName() const;

private:
	std::string		m_ParamName;
};
typedef nbObjectPtrDerive<ArgumentException, nb::Core::ExceptionPtr>	ArgumentExceptionPtr;

//空传递给不接受它作为有效参数的方法时引发的异常
class NB_EXPORT ArgumentNullException : public ArgumentException
{
public:
	ArgumentNullException(const char *paramName);
	ArgumentNullException(const char *paramName, const char *message);

};
typedef nbObjectPtrDerive<ArgumentNullException, ArgumentExceptionPtr>	ArgumentNullExceptionPtr;

//参数值超出调用的方法所定义的允许取值范围时引发的异常
class NB_EXPORT ArgumentOutOfRangeException : public ArgumentException
{
public:
	ArgumentOutOfRangeException(const char *paramName, void *v, void *lowBound, void *upBound);
	ArgumentOutOfRangeException(const char *paramName, void *v, void *lowBound, void *upBound, const char *message);

	void *GetLowBound() const;
	void *GetUpBound() const;
	void *GetValue() const;

private:
	void	*m_LowBound;
	void	*m_UpBound;
	void	*m_V;
};
typedef nbObjectPtrDerive<ArgumentOutOfRangeException, ArgumentExceptionPtr>	ArgumentOutOfRangeExceptionPtr;


}}
