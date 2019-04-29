#include "TestApp.h"
#include "TestRectanglePage.h"

using namespace nb::gui;
TestApp::TestApp(void)
{
}

TestApp::~TestApp(void)
{
}

void TestApp::Test()
{
	Window w;
	w.Width = 10;
	this->run();
}
