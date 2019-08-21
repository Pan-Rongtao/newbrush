#pragma once
#include "../TestBase.h"
#include "core/Window.h"

using namespace nb;

class TestWindow : public TestBase
{
public:
	void test();

	void onResize(const Window::ResizeArgs &args);
	void onMouseEnter(const Window::MouseEnterEventArgs &args);
	void onMouseLeave(const Window::MouseLeaveEventArgs &args);
	void onMouseMove(const Window::MouseMoveEventArgs &args);
	void onMouseLeftButton(const Window::MouseLeftButtonEventArgs &args);
	void onMouseRightButton(const Window::MouseRightButtonEventArgs &args);
	void onMouseMiddleButton(const Window::MouseMiddleButtonEventArgs &args);
	void onMouseWheel(const Window::MouseWheelEventArgs &args);
	void onKeyAction(const Window::KeyEventArgs &args);
};