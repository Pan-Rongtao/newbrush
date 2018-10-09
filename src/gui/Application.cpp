#include "gui/Application.h"
#include "core/Exception.h"

using namespace nb::core;
using namespace nb::gui;

static std::shared_ptr<Application> g_app;
Application::Application()
{
	if (!g_app)	throw LogicException(__FILE__, __LINE__);
	g_app = std::shared_ptr<Application>(this);
	Windows.setGetter(std::bind(&Application::m_windows, this));
}

Application::~Application()
{
}

std::shared_ptr<Application> Application::current()
{
	if (!g_app)
		g_app = std::make_shared<Application>();
	return g_app;
}

int Application::run()
{
	try
	{
		return nb::gl::Application::run();
	}
	catch(Exception &e)
	{
		printf("exception: %s\r\n", e.what().data());
	}
	catch(...)
	{
		printf("other exception\r\n");
	}
	return 1;
}
