#include "TestException.h"
#include <core/Exception.h>

using namespace nb::core;
void TestException::test()
{
//	throw Exception();
//	throw Exception("123");

//	NB_THROW_EXCEPTION("xxx");

//	throw ArgumentException("param0", __FILE__, __LINE__);
//	throw ArgumentNullException("param1", __FILE__, __LINE__);
//	throw ArgumentOutOfRangeException("param2", 0, 9, -1, __FILE__, __LINE__);

//	throw ArithmeticException(__FILE__, __LINE__);
//	throw DivideByZeroException(__FILE__, __LINE__);

//	throw ArrayException(__FILE__, __LINE__);
//	throw ArrayIndexOutOfRangeException(10, 10, __FILE__, __LINE__);
//	throw ArrayDimensionException(3, 4, __FILE__, __LINE__);

//	throw SystemException(__FILE__, __LINE__);
//	throw LogicException(__FILE__, __LINE__);
//	throw BadTimingOperationException(__FILE__, __LINE__);

//	throw IOException("io", __FILE__, __LINE__);
//	throw FileNotFoundException("d:/1.txt", __FILE__, __LINE__);
//	throw DirectoryNotFoundException("d:/dir", __FILE__, __LINE__);
//	throw EndOfStreamException("d:/stream.txt", __FILE__, __LINE__);
//	throw FileLoadFailedException("d:/pic.jpg", __FILE__, __LINE__);
	throw PathTooLongException("d:/1/2/3/4/5/6/7/8/9/11", 256, __FILE__, __LINE__);
}