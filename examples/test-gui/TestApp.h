#pragma once
#include "../TestBase.h"
#include "gui/Application.h"
#include "gui/Window.h"
#include "gui/Shape.h"

using namespace nb;
using namespace nb::gui;

class MyApp : public Application
{
public:

protected:
	virtual void onActivated(const EventArgs &args) override;
	virtual void onDeactivated(EventArgs &args) override;
	virtual void onExit(const ExitEventArgs &args) override;
	virtual void onLoadCompleted(const EventArgs &args) override;
	virtual void onSessionEnding(const SessionEndingCancelEventArgs &args) override;
	virtual void onStartUp(const StartupEventArgs &args) override;
};

class TestApp : public TestBase
{
public:
	virtual void test();

};
