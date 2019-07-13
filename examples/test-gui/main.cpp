#include "../TestBase.h"
#include "gui/Application.h"
#include "TestWindow.h"
#include "TestApp.h"
#include "TestCanvas.h"
#include "TestStackPanel.h"
#include "TestWrapPanel.h"
#include "TestDockPanel.h"
#include "TestEasingFunction.h"
#include "TestTimeline.h"
#include "TestPropertyAnimation.h"
#include "TestPropertyAnimationUsingKeyFrames.h"
#include "TestStoryboard.h"
#include "TestTextBlock.h"

using namespace nb::core;
int main(int argc, char *argv[])
{
	try{
		Application app;
		TestHandle<TestPropertyAnimation> test;
		test->test();
		return app.run();
	}
	catch (std::exception &e)
	{
		printf("exception: %s\r\n", e.what());
	}
	catch (...)
	{
		printf("other exception.\r\n");
	}

	return 0;
}
