#include "gui/Application.h"
#include "core/Timer.h"
#include "gui/Window.h"
#include "WindowCollections.h"

using namespace nb::core;
using namespace nb::gui;

Application *g_app = nullptr;
Application::Application()
{
	if (g_app)
		NB_THROW_EXCEPTION(std::logic_error, "create tow application");

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
	Timer::drive();
}

int Application::run()
{
	try 
	{
		for (auto w : WindowCollections::Windows())
		{
			w->init();
			w->measure(Size((float)w->Width, (float)w->Height));
			w->arrage(Rect(0.0f, 0.0f, (float)w->Width, (float)w->Height));
			w->onRender(w->DrawContext());
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
