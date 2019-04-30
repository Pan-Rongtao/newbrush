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
	w.Content = std::make_shared<Panel>();
	this->run();
}
