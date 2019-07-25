#pragma once
#include "../TestBase.h"
#include "gui/UniformGrid.h"
#include "gui/Window.h"

using namespace nb::core;
using namespace nb::gui;

class TestUniformGrid : public TestBase
{
public:
	void test();

	nb::gui::Window m_window;
};