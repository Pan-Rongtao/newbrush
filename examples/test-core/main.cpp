#include "../TestBase.h"
#include "TestVec.h"
#include "TestVecB.h"
#include "TestVecI.h"
#include "TestException.h"
#include "TestProperty.h"
#include "TestColor.h"
#include "TestDateTime.h"
#include "TestTimer.h"
#include "TestTimeSpan.h"

int main(int argc, char *argv[])
{
	try {
		TestHandle<TestDateTime> test;
		test->test();
	}
	catch (std::exception &e)
	{
		printf("%s\r\n", e.what());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
