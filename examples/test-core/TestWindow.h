#pragma once
#include "../TestBase.h"
#include "core/Window.h"

using namespace nb::core;

class TestWindow : public TestBase
{
public:
	void test();


	void OnResize(const nb::core::Window::ResizeArgs &args);
	void OnMouseAction(const nb::core::Window::MouseEventArgs &args);
	void OnKeyAction(const nb::core::Window::KeyEventArgs &args);
};