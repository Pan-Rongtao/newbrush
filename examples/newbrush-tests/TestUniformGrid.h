#pragma once
#include "../TestBase.h"
#include "gui/UniformGrid.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gui;

class TestUniformGrid : public TestBase
{
public:
	void test();

	std::shared_ptr<nb::gui::Window> m_window;
};