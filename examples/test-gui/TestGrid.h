#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/Grid.h"

using namespace nb::gui;
class TestGrid : public TestBase
{
public:
	virtual void test() override;

	nb::gui::Window m_window;
};