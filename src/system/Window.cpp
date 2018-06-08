#include "system/Window.h"
#include "system/Platform.h"
#include "core/Exception.h"
#include "NativeWindow.h"
#include "Window_Win32.h"
#include "Window_X11.h"
#include "Window_Wayland.h"

using nb::System::PointI;
using nb::System::SizeI;
using nb::System::RectI;
using nb::System::Window;
using nb::System::WindowEvent;

Window::Window()
{
	CreateNative();
}

Window::Window(int width, int height)
{
	CreateNative();
	SetSize(SizeI(width, height));
}

Window::Window(int x, int y, int width, int height)
{
	CreateNative();
	SetRect(RectI(x, y, width, height));
}

Window::Window(const nb::System::String &caption)
{
	CreateNative();
	SetCaption(caption);
}

Window::Window(const nb::System::String &caption, int width, int height)
{
	CreateNative();
	SetCaption(caption);
	SetSize(SizeI(width, height));
}

Window::Window(const nb::System::String &caption, const nb::System::RectI &rect)
{
	CreateNative();
	SetCaption(caption);
	SetRect(rect);
}

Window::~Window()
{
	ReleaseNative();
}

void Window::SetCaption(const nb::System::String &caption)
{
	m_pNative->SetCaption(caption);
}

nb::System::String Window::GetCaption() const
{
	return m_pNative->GetCaption();
}

void Window::SetX(int x)
{
	SetRect(RectI(x, GetPos().GetY(), GetWidth(), GetHeight()));
}

int Window::GetX() const
{
	return GetRect().GetX();
}

void Window::SetY(int y)
{
	SetRect(RectI(GetPos().GetX(), y, GetWidth(), GetHeight()));
}

int Window::GetY() const
{
	return GetRect().GetY();
}

void Window::SetWidth(int width)
{
	SetRect(RectI(GetPos(), width, GetHeight()));
}

int Window::GetWidth() const
{
	return GetRect().GetWidth();
}

void Window::SetHeight(int height)
{
	SetRect(RectI(GetPos(), GetWidth(), height));
}

int Window::GetHeight() const
{
	return GetRect().GetHeight();
}

void Window::SetPos(const nb::System::PointI &pos)
{
	SetRect(RectI(pos, GetWidth(), GetHeight()));
}

void Window::SetPos(int x, int y)
{
	SetPos(PointI(x, y));
}

nb::System::PointI Window::GetPos() const
{
	return GetRect().GetLeftTop();
}

void Window::SetSize(const nb::System::SizeI &size)
{
	SetRect(RectI(GetPos(), size));
}

nb::System::SizeI Window::GetSize() const
{
	return nb::System::SizeI(GetWidth(), GetHeight());
}

void Window::SetRect(const nb::System::RectI &rect)
{
	if(rect.GetWidth() < 0 || rect.GetHeight() < 0)
		NB_THROW_EXCEPTION("invalid window size.");

	m_pNative->SetRect(rect);
}

nb::System::RectI Window::GetRect() const
{
	return m_pNative->GetRect();
}

void Window::Pending()
{
	m_pNative->Pending();
}
/*
void Window::Peek()
{
//	m_pNative->Pending();
}
*/

void Window::SetListener(WindowEvent *listener)
{
	m_pListener = listener;
}

WindowEvent *Window::GetListener() const
{
	return m_pListener;
}

long Window::GetWindowHandle() const
{
	return (long)m_pNative->GetWindowHandle();
}

void Window::CreateNative()
{
	m_pListener = NULL;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	m_pNative = new Window_Win32(this);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11
	m_pNative = new Window_X11(this);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	m_pNative = new Window_Wayland(this);
#else
	#error "not complite fun [Window::Window()] in file Windows.cpp"
#endif
//	if(m_pListener)
//		m_pListener->OnPrimaryAction(WindowEvent::PrimaryAction_Create);
}

void Window::ReleaseNative()
{
	delete m_pNative;
	m_pNative = NULL;
}
