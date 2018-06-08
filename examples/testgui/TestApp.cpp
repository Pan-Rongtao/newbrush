#include "TestApp.h"
#include "TestRectanglePage.h"

using nb::Gui::Window;
TestApp::TestApp(void)
{
	m_Window = new TestWindow();
}

TestApp::~TestApp(void)
{
}

void TestApp::Test()
{
	this->Run();
}
