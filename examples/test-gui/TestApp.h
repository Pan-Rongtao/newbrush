#pragma once
#include "../TestBase.h"
#include "gui/Application.h"
#include "gui/Window.h"

using namespace nb::core;
using namespace nb::gui;

class TestApp : public TestBase
{
public:
	virtual void test();

private:
	Window m_window;
};
