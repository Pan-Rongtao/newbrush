#include "gui/Application.h"
#include "core/Timer.h"
#include "gui/Window.h"
#include "WindowCollections.h"

using namespace nb;
using namespace nb::gui;

Application *Application::g_app = nullptr;
Application::Application()
{
	if (g_app)
		nbThrowException(std::logic_error, "create tow application");

	g_app = this;
}

Application::~Application()
{
}

Application *Application::current()
{
	return g_app;
}

void Application::preRender()
{
	Timer::driveInLoop();
}

int Application::run()
{
	try 
	{
		for (auto w : WindowCollections::Windows)
		{
			w->updateLayout();
		}
		return nb::gl::Application::run();
	}
	catch (std::exception &e)
	{
		printf("exception:%s\r\n", e.what());
	}
	catch(...)
	{
		printf("other exception\r\n");
	}
	return 1;
}
