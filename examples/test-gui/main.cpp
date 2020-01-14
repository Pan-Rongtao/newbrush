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
#include "TestBinding.h"
#include "TestBrush.h"
#include "TestProperty.h"
#include "TestLine.h"
#include "TestPolyline.h"
#include "TestEllipse.h"
#include "TestPolygon.h"
#include "GLES2/gl2.h"
#include "TestUIElement.h"
/*
int main(int argc, char *argv[])
{
	bool b = glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	auto m_implWindow = glfwCreateWindow(800, 600, "newbrush", nullptr, nullptr);
	glfwMakeContextCurrent(m_implWindow);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto e = glGetError();

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_implWindow);
		glfwWaitEvents();
	}
	return 0;
}
*/

int main(int argc, char *argv[])
{
	try{
		Application app;
		TestHandle<TestBinding> test;
		test->test();
		return app.run(argc, argv);
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
	/*
	TestHandle<TestApp> test;
	test->test();
	return 0;*/
}
