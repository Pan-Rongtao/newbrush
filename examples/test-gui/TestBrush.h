#pragma once
#include "../TestBase.h"
#include "gui/GradientBrush.h"
#include "gui/Shape.h"
#include "gui/Rectangle.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gui;

class TestBrush : public TestBase
{
public:
	void test();


private:
	std::shared_ptr<nb::gui::Window> m_window;
};