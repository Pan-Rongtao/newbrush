#include "gui/Application.h"
#include "core/Exception.h"
#include "core/Timer.h"
#include "gui/Window.h"
#include "WindowCollections.h"

using namespace nb::core;
using namespace nb::gui;

static std::shared_ptr<Application> g_app;
Application::Application()
{
	if (g_app)	throw std::logic_error("create tow application");
	g_app = std::shared_ptr<Application>(this);
}

Application::~Application()
{
}

std::shared_ptr<Application> Application::current()
{
	return g_app;
}

void Application::PreRenderOverride()
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
	catch(Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
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
