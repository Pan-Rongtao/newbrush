#include "NativeWindow.h"
#include "system/Window.h"

using nb::System::Window;
using nb::System::NativeWindow;
using nb::System::WindowEvent;

std::map<long, Window *> nb::System::NativeWindow::m_mapInternals;
NativeWindow::NativeWindow(Window *pW)
: m_pW(pW)
{
}

NativeWindow::~NativeWindow()
{
}

void NativeWindow::OnPrimaryAction(Window *pW, WindowEvent::PrimaryAction action)
{
	if(pW->GetListener())
		pW->GetListener()->OnPrimaryAction(action);
}

void NativeWindow::OnResize(Window *pW, int width, int height)
{
	if(pW->GetListener())
		pW->GetListener()->OnResize(width, height);
}

void NativeWindow::OnKeyAction(Window *pW, WindowEvent::KeyAction action, WindowEvent::KeyCode key, int mask)
{
	if(pW->GetListener())
		pW->GetListener()->OnKeyAction(action, key, mask);
}

void NativeWindow::OnPointerAction(Window *pW, WindowEvent::PointerAction action, int x, int y)
{
	if(pW->GetListener())
		pW->GetListener()->OnPointerAction(action, x, y);
}
