#pragma once
#include "../TestBase.h"
#include "gui/DockPanel.h"
#include "gui/Window.h"
#include "gui/Rectangle.h"

using namespace nb::core;
using namespace nb::gui;

class TestDockPanel : public TestBase
{
public:
	void test();

	Window m_window;
};