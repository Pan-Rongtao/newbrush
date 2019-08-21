#pragma once
#include "../TestBase.h"
#include "gui/DockPanel.h"
#include "gui/Window.h"
#include "gui/Rectangle.h"

using namespace nb;
using namespace nb::gui;

class TestDockPanel : public TestBase
{
public:
	void test();

	std::shared_ptr<nb::gui::Window> m_window;
};