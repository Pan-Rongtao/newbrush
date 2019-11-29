#include "gui/Application.h"
#include "core/Timer.h"
#include "gui/Window.h"
#include "gles/Egl.h"
#include "../gles/EglMaster.h"
#include "core/Log.h"
#include <GLES2/gl2.h>

using namespace nb;
using namespace nb::gui;

Application *Application::g_app = nullptr;
Application::Application()
	: m_mainWindow(nullptr)
{
	if (g_app)
		nbThrowException(std::logic_error, "create tow application");

	g_app = this;
	Window::init();
}

Application::~Application()
{
	Window::deinit();
}

Application *Application::current()
{
	return g_app;
}

std::vector<gui::Window*> &Application::windows()
{
	return m_windows;
}

void Application::setMainWindow(Window * w)
{
	auto iter = std::find(m_windows.begin(), m_windows.end(), w);
	if (iter != m_windows.end())
		m_mainWindow = w;
}

Window * Application::mainWindow()
{
	return m_mainWindow ? m_mainWindow : (m_windows.empty() ? nullptr : m_windows[0]);
}

int Application::run()
{
	try 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
		while (true)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Timer::driveInLoop();
			render();
			for (auto const &w : Application::current()->windows())
				w->swapBuffers();
			Window::waitEvent();
		}
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

void Application::shutdown()
{
}

void Application::shutdown(int exitCode)
{
}

void Application::render()
{
	static int frames = 0;
	static uint64_t k = nb::getTickCount();
	for (auto const &context : gl::EglMaster::contexts())
		context->draw();

	++frames;
	uint64_t kk = nb::getTickCount();
	if (kk - k >= 2000)
	{
		float fps = frames * 1000.0f / (kk - k);
		frames = 0;
		k = kk;
		Log::info("fps:%.2f", fps);
	}
}
