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
	Log::info("onActivated.");
}

void MyApp::onDeactivated(EventArgs & args)
{
	Log::info("onDeactivated.");
}

void MyApp::onExit(const ExitEventArgs & args)
{
	Log::info("onExit: exitCode=%d.", args.exitCode);
}

void MyApp::onLoadCompleted(const EventArgs & args)
{
	Log::info("onLoadCompleted.");
}

void MyApp::onSessionEnding(const SessionEndingCancelEventArgs & args)
{
	Log::info("onSessionEnding: reason=%d", args.reason);
}

void MyApp::onStartUp(const StartupEventArgs & args)
{
	Log::info("onStartUp.");
}

void TestApp::test()
{
	auto w0 = std::make_shared<Window>();

	MyApp app;
	app.Startup += [](const StartupEventArgs &args) {Log::info("Startup Event."); };
	char *argv[10] = { "1", "2", "3" };
	app.run(3, argv);
}
