#pragma once
#include "../TestBase.h"
#include "gui/StackPanel.h"
#include "gui/Window.h"
#include "gui/Shape.h"

using namespace nb;
using namespace nb::gui;

class TestStackPanel : public TestBase
{
public:
	void test();

	std::shared_ptr<nb::gui::Window> m_window;
};