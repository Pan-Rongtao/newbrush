#include "../TestBase.h"
#include "TestException.h"
#include "TestColor.h"
#include "TestDateTime.h"
#include "TestTimer.h"
#include "TestTimeSpan.h"
#include "TestRandom.h"
#include "TestEvent.h"
#include "TestRect.h"
#include "TestEasingFunction.h"
#include "TestWindow.h"

int main(int argc, char *argv[])
{
	try {
		TestHandle<TestRandom> test;
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
