#include "../TestBase.h"
#include "TestVec.h"
#include "TestVecB.h"
#include "TestVecI.h"
#include "TestException.h"
#include "TestProperty.h"
#include "core/Exception.h"

int main(int argc, char *argv[])
{
	try {
		TestHandle<TestProperty> test;
		test->test();
	}
	catch (nb::core::Exception &e)
	{
		printf("%s\r\n", e.what().data());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
