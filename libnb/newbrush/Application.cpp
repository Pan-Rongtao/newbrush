#include "newbrush/Application.h"
#include "newbrush/Timer.h"
#include "newbrush/Log.h"

using namespace nb;

void MessageQueue::post(const Task &task)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_msgQueue.push(task);
}

MessageQueue::Task MessageQueue::pick()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_msgQueue.empty()) return nullptr;

	auto task = m_msgQueue.front();
	m_msgQueue.pop();
	return task;
}

Application *g_app = nullptr;
Application::Application()
	: m_shutdownMode(ShutdownModeE::OnLastWindowClose)
	, m_exitFlag(false)
	, m_resources(createRef<ResourceDictionary>())
{
	nbThrowExceptionIf(g_app, std::logic_error, "create two application");
	g_app = this;
	WindowCollection::get()->WindowClosed += std::bind(&Application::onWindowClosed, this, std::placeholders::_1);
	WindowCollection::get()->WindowFocus += std::bind(&Application::onWindowFocused, this, std::placeholders::_1);
}

Application *Application::get()
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
	return *WindowCollection::get();
}

void Application::setMainWindow(Window * w)
{
	WindowCollection::get()->setMainWindow(w);
}

Window * Application::mainWindow()
{
	return WindowCollection::get()->mainWindow();
}

ref<ResourceDictionary> Application::resources()
{
	return m_resources;
}

int Application::run(int argc, char *argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i)
	{
		args.push_back(argv[i]);
	}
	onStartUp({ args });

	try
	{
		while (!m_exitFlag)
		{
			auto task = m_msgQueue.pick();
			if (task)
			{
				task();
			}
			for (auto const &w : WindowCollection::get()->windows())
			{
				w->render();
			}
			Timer::driveInLoop();
			Window::pollEvents();
		}
	}
	catch (std::exception &e) { UnhandledException.invoke({ e }); }
	catch (...) { UnhandledExtraException.invoke({}); }
	return 0;
}

void Application::shutdown(int exitCode)
{
	m_exitFlag = true;
	for (auto const &w : WindowCollection::get()->windows())
	{
		w->_close(false);
	}

	WindowCollection::get()->windows().clear();
	onExit({ exitCode });
}

void Application::post(const MessageQueue::Task &task)
{
	m_msgQueue.post(task);
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

void Application::onWindowClosed(const bool &isMain)
{
	auto mode = shutdownMode();
	if ((mode == ShutdownModeE::OnLastWindowClose && WindowCollection::get()->windows().empty())
		|| (mode == ShutdownModeE::OnMainWindowClose && isMain)
		|| (mode == ShutdownModeE::OnExplicitShutdown && WindowCollection::get()->windows().empty() && m_exitFlag))
	{
		shutdown();
	}
}

void Application::onWindowFocused(const bool &focused)
{
	if (focused)
	{

	}
	else
	{

	}
}
