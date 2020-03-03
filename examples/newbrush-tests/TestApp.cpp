#include "newbrush/gui/Application.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Image.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/core/Color.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/core/Log.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

class MyApp : public Application
{
public:

protected:
	virtual void onActivated(const EventArgs &args) override
	{
		Log::info("MyApp::onActivated.");
	}
	virtual void onDeactivated(EventArgs &args) override
	{
		Log::info("MyApp::onDeactivated.");
	}
	virtual void onExit(const ExitEventArgs &args) override
	{
		Log::info("MyApp::onExit: exitCode=%d.", args.exitCode);
		Application::onExit(args);
	}
	virtual void onLoadCompleted(const EventArgs &args) override
	{
		Log::info("MyApp::onLoadCompleted.");
	}
	virtual void onSessionEnding(const SessionEndingCancelEventArgs &args) override
	{
		Log::info("MyApp::onSessionEnding: reason=%d", args.reason);
	}
	virtual void onStartUp(const StartupEventArgs &args) override
	{
		Log::info("MyApp::onStartUp.");
	}
};

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

TEST_CASE("Test nb::Application", "[Application]")
{
	MyApp app;
	app.setShutdownMode(ShutdownModeE::OnLastWindowClose);
	app.Startup += [](const StartupEventArgs &args) {Log::info("App Startup Event."); };
	app.Exit += [](const ExitEventArgs &args) {Log::info("App exit Event. exitCode=%d", args.exitCode); };
	char *argv[10] = { "1", "2", "3" };


	auto w0 = std::make_shared<MyWindow>();
	w0->setValue(Window::TitleProperty(), std::string("window0"));
	//w0->Icon = std::make_shared<ImageSource>("e:/Pics/3.jpg");
	w0->Closed += [&app](const EventArgs &args) {Log::info("closed event."); /*app.shutdown();*/ };
	w0->Closing += [](CancelEventArgs &args) { args.cancel = true; Log::info("closing event. cancel=%s", args.cancel ? "true" : "false");  };
	auto w1 = std::make_shared<MyWindow>();
	w1->setValue(Window::TitleProperty(), std::string("window1"));


	app.run(3, argv);
}
