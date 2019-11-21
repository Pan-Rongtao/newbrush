#pragma once
#include "../TestBase.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gui;

class TestEllipse : public TestBase
{
public:
	void test();


private:
	std::shared_ptr<nb::gui::Window> m_window;
};