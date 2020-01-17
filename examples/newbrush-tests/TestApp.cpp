#include "TestApp.h"
#include "gui/Image.h"
#include "gui/Shape.h"
#include "core/Color.h"
#include "gui/Rectangle.h"
#include "media/ImageSource.h"
#include "media/SolidColorBrush.h"
#include "core/Log.h"

using namespace nb;
using namespace nb::gui;
void MyApp::onActivated(const EventArgs & args)
{
	Log::info("MyApp::onActivated.");
}

void MyApp::onDeactivated(EventArgs & args)
{
	Log::info("MyApp::onDeactivated.");
}

void MyApp::onExit(const ExitEventArgs & args)
{
	Log::info("MyApp::onExit: exitCode=%d.", args.exitCode);
	Application::onExit(args);
}

void MyApp::onLoadCompleted(const EventArgs & args)
{
	Log::info("MyApp::onLoadCompleted.");
}

void MyApp::onSessionEnding(const SessionEndingCancelEventArgs & args)
{
	Log::info("MyApp::onSessionEnding: reason=%d", args.reason);
}

void MyApp::onStartUp(const StartupEventArgs & args)
{
	Log::info("MyApp::onStartUp.");
}

class MyWindow : public Window
{
public:
	virtual void onActivated(const EventArgs &args) override
	{
		Log::info("MyWindow::onActivated.");
		Window::onActivated(args);
	}
	virtual void onDeactivated(const EventArgs &args) override
	{
		Log::info("MyWindow::onDeactivated.");
		Window::onDeactivated(args);
	}
	virtual void onClosed(const EventArgs &args) override
	{
		Log::info("MyWindow::onClosed.");
		Window::onClosed(args);
	}
	virtual void onClosing(const CancelEventArgs &args) override
	{
		Log::info("MyWindow::onClosing.");
		Window::onClosing(args);
	}
	virtual void onLocationChanged(const EventArgs &args) override
	{
		Log::info("MyWindow::onLocationChanged.");
		Window::onLocationChanged(args);
	}
	virtual void onStateChanged(const EventArgs &args) override
	{
		Log::info("MyWindow::onStateChanged.");
		Window::onStateChanged(args);
	}
	virtual void onSourceInitiallized(const EventArgs &args) override
	{
		Log::info("MyWindow::onSourceInitiallized.");
		Window::onSourceInitiallized(args);
	}
	virtual void onContentRendered(const EventArgs &args) override
	{
		Log::info("MyWindow::onContentRendered.");
		Window::onContentRendered(args);
	}
};

void TestApp::test()
{
	MyApp app;
	app.setShutdownMode(ShutdownModeE::OnExplicitShutdown);
	app.Startup += [](const StartupEventArgs &args) {Log::info("App Startup Event."); };
	app.Exit += [](const ExitEventArgs &args) {Log::info("App exit Event. exitCode=%d", args.exitCode); };
	char *argv[10] = { "1", "2", "3" };


	auto w0 = std::make_shared<MyWindow>();
	w0->set(Window::TitleProperty(), std::string("window0"));
	//w0->Icon = std::make_shared<ImageSource>("e:/Pics/3.jpg");
	w0->Closed += [&app](const EventArgs &args) {Log::info("closed event."); /*app.shutdown();*/ };
	w0->Closing += [](CancelEventArgs &args) { args.cancel = false; Log::info("closing event. cancel=%s", args.cancel ? "true" : "false");  };
	auto w1 = std::make_shared<MyWindow>();
	w1->set(Window::TitleProperty(), std::string("window1"));


	app.run(3, argv);
}
