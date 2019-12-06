#include "gui/Application.h"
#include "core/Timer.h"
#include "gui/Window.h"
#include "gles/Egl.h"
#include "../gles/EglMaster.h"
#include "core/Log.h"
#include <GLES2/gl2.h>
#include "core/Singleton.h"

using namespace nb;
using namespace nb::gui;

Application *Application::g_app = nullptr;
Application::Application()
	: m_shutdownMode(ShutdownModeE::OnLastWindowClose)
	, m_mainWindow(nullptr)
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

void Application::setShutdownMode(ShutdownModeE mode)
{
	m_shutdownMode = mode;
}

ShutdownModeE Application::shutdownMode() const
{
	return m_shutdownMode;
}

const WindowCollection &Application::windows() const
{
	return *Singleton<WindowCollection>::get();
}

void Application::setMainWindow(Window * w)
{
	auto iter = std::find(Singleton<WindowCollection>::get()->windows().begin(), Singleton<WindowCollection>::get()->windows().end(), w);
	if (iter != Singleton<WindowCollection>::get()->windows().end())
		m_mainWindow = w;
}

Window * Application::mainWindow()
{
	return m_mainWindow ? m_mainWindow : (Singleton<WindowCollection>::get()->windows().empty() ? nullptr : Singleton<WindowCollection>::get()->windows()[0]);
}

int Application::run(int argc, char *argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i)
	{
		args.push_back(argv[i]);
	}
	onStartUp({ args });

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
	try
	{
		while (true)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Timer::driveInLoop();
			render();
			for (auto const &w : Singleton<WindowCollection>::get()->windows())
			{
				if (w->Visibility == VisibilityE::Visible)
				{
					w->swapBuffers();
				}
			}
			Window::waitEvent();
		}
	}
	catch (std::exception &e)	{ UnhandledException.invoke({ e }); }
	catch (...)					{ UnhandledExtraException.invoke({}); }
	return 1;
}

void Application::shutdown()
{
	shutdown(0);
}

void Application::shutdown(int exitCode)
{
	Window::deinit();
	onExit(ExitEventArgs{ exitCode });
}

void Application::onActivated(const EventArgs & args)
{
	Activated.invoke(args);
}

void Application::onDeactivated(EventArgs & args)
{
	Deactivated.invoke(args);
}

void Application::onExit(const ExitEventArgs & args)
{
	Exit.invoke(args);
}

void Application::onLoadCompleted(const EventArgs & args)
{
	LoadCompleted.invoke(args);
}

void Application::onSessionEnding(const SessionEndingCancelEventArgs & args)
{
	SessionEnding.invoke(args);
}

void Application::onStartUp(const StartupEventArgs & args)
{
	Startup.invoke(args);
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
