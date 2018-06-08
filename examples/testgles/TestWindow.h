#pragma once
#include "system/Window.h"
#include "system/WindowEvent.h"
#include "TestBase.h"

class TestWindow : public TestBase, public nb::System::WindowEvent
{
public:

	void Test();

private:
	virtual void OnPrimaryAction(nb::System::WindowEvent::PrimaryAction action);
	virtual void OnResize(int width, int height);
	virtual void OnPointerAction(nb::System::WindowEvent::PointerAction action, int x, int y);
	virtual void OnKeyAction(nb::System::WindowEvent::KeyAction action, KeyCode key, int mask);

	nb::System::Window	*m_Window;
};
