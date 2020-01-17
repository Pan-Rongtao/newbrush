#pragma once
#include "../TestBase.h"
#include "gui/Button.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gui;
class TestButton : public TestBase
{
public:
	void test();

	void onBtnMouseLeftButtonDown(const MouseButtonEventArgs &args);
	void onBtnMouseLeftButtonUp(const MouseButtonEventArgs &args);
	void onBtnClick(const Button::ClickArgs &args);

	std::shared_ptr<Button> m_btn;
	std::shared_ptr<nb::gui::Window> m_window;
};