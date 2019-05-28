#pragma once
#include "../TestBase.h"
#include "gui/StackPanel.h"
#include "gui/Window.h"
#include "gui/Rectangle.h"

using namespace nb::core;
using namespace nb::gui;

class TestStackPanel : public TestBase
{
public:
	void test();

	Window m_window;
};