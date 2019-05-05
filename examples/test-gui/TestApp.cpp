#include "TestApp.h"
#include "TestRectanglePage.h"

using namespace nb::gui;
void TestApp::test()
{
	Window w;
	w.Content = std::make_shared<Panel>();
	this->run();
}
