#include "../TestBase.h"
#include "gui/Application.h"
#include "TestWindow.h"
#include "TestApp.h"
#include "TestCanvas.h"
#include "TestStackPanel.h"
#include "TestWrapPanel.h"
#include "TestDockPanel.h"
#include "TestTimeline.h"
#include "TestPropertyAnimation.h"
#include "TestPropertyAnimationUsingKeyFrames.h"
#include "TestStoryboard.h"
#include "TestTextBlock.h"
#include "TestGrid.h"
#include "TestUniformGrid.h"
#include "TestButton.h"

int main(int argc, char *argv[])
{
	try{
		Application app;
		TestHandle<TestGrid> test;
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
