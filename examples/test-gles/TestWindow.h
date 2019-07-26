#pragma once
#include "core/Window.h"
#include "../TestBase.h"

class TestWindow : public TestBase
{
public:
	void test();

private:
	void OnResize(const nb::core::Window::ResizeArgs &args);
	void OnMouseAction(const nb::core::Window::MouseEventArgs &args);
	void OnKeyAction(const nb::core::Window::KeyEventArgs &args);

	nb::core::Window	*m_window;
	nb::core::Window	*m_window1;
};
