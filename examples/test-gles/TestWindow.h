#pragma once
#include "system/Window.h"
#include "TestBase.h"

class TestWindow : public TestBase
{
public:

	void Test();

private:
	void OnResize(const nb::System::Window::ResizeArgs &args);
	void OnPointerAction(const nb::System::Window::PointerEventArgs &args);
	void OnKeyAction(const nb::System::Window::KeyEventArgs &args);

	nb::System::Window	*m_window;
};
