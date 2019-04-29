#pragma once
#include "core/Window.h"
#include "TestBase.h"

class TestWindow : public TestBase
{
public:

	void Test();

private:
	void OnResize(const nb::core::Window::ResizeArgs &args);
	void OnPointerAction(const nb::core::Window::PointerEventArgs &args);
	void OnKeyAction(const nb::core::Window::KeyEventArgs &args);

	nb::core::Window	*m_window;
	nb::core::Window	*m_window1;
};
