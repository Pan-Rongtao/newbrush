#include "gui/Window.h"
#include "Window_Internal.h"
#include "WindowManager.h"

using nb::Gui::Window;
using nb::Gui::Panel;
using nb::Gui::Page;
using nb::Gui::UIElement;
using nb::Gui::WindowManager;

Window::Window()
{
	m_internal = new Window_Internal(this);
	WindowManager::Push(this);
}

Window::~Window()
{
	delete m_internal;
	WindowManager::Erease(this);
}

void Window::SetPage(Page *page)
{
	m_internal->SetPage(page);
	page->m_window = this;
}

void Window::Render()
{
	m_internal->Render();
}
