#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/Grid.h"

using namespace nb::gui;
class TestGrid : public TestBase
{
public:
	virtual void test() override;

	std::shared_ptr<nb::gui::Window> m_window;
};