#pragma once
#include "TestBase.h"
#include "gui/Window.h"
#include "TestPageBase.h"

class TestWindow :public nb::Gui::Window, public TestBase
{
public:
	TestWindow();
	~TestWindow();

	virtual void Test();

private:
	TestPageBasePtr			m_RootPage;
};

typedef nbObjectPtrDerive<TestWindow, nb::Gui::WindowPtr>	TestWindowPtr;
