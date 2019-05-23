#include "../TestBase.h"
#include "core/Exception.h"
#include "TestWindow.h"
#include "TestApp.h"
#include "TestEasingFunction.h"
#include "TestTimeline.h"
#include "TestPropertyAnimation.h"
#include "TestPropertyAnimationUsingKeyFrames.h"
#include "TestStoryboard.h"

using namespace nb::core;
int main(int argc, char *argv[])
{
	try{
		TestHandle<TestStoryboard> test;
		test->test();
	}
	catch (Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
