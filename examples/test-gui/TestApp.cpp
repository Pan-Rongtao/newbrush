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
	auto panelRoot = std::make_shared<Panel>();
	w.Content = panelRoot;
	this->run();
}
