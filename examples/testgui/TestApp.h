#pragma once
#include "TestBase.h"
#include "gui/Application.h"
#include "TestWindow.h"

class TestApp : public nb::Gui::Application, public TestBase
{
public:
	TestApp();
	~TestApp();

	virtual void Test();

private:
	TestWindowPtr			m_Window;
};
