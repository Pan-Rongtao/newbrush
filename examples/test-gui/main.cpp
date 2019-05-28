#include "../TestBase.h"
#include "core/Exception.h"
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

using namespace nb::core;
int main(int argc, char *argv[])
{
	try{
		Application app;
		TestHandle<TestDockPanel> test;
		test->test();
		return app.run();
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
