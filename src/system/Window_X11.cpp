#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11
#include "Window_X11.h"
#include "core/Exception.h"
#include "system/Window.h"

using nb::System::String;
using nb::System::RectI;
using nb::System::WindowEvent;
using nb::System::Window;
using nb::System::Window_X11;
Window_X11::Window_X11(Window *pW)
: NativeWindow(pW)
, m_rect(100, 100, 800, 480)
{
	m_X11Display = XOpenDisplay(NULL);
	if(m_X11Display == NULL)
		NB_THROW_EXCEPTION("fail in fun [XOpenDiplay]");
	int screen = DefaultScreen(m_X11Display);	//这是个宏

	//m_X11WindowID从服务端获取，不用释放
	m_X11WindowID = XCreateSimpleWindow(m_X11Display, RootWindow(m_X11Display, screen), m_rect.GetX(), m_rect.GetY(), m_rect.GetWidth(), m_rect.GetHeight(), 1, BlackPixel(m_X11Display, screen), WhitePixel(m_X11Display, screen));

	XSelectInput(m_X11Display, m_X11WindowID, StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);
	XMapWindow(m_X11Display, m_X11WindowID);

//	KeySym xx[1] = {97};
//	XChangeKeyboardMapping(m_X11Display, 10, 1, xx, 1);
//	XModifierKeymap *keymap = XNewModifiermap(2);
//	keymap = XInsertModifiermapEntry(keymap, 55, 11);
//	XSetModifierMapping(m_X11Display, keymap);
}

Window_X11::~Window_X11()
{
	XCloseDisplay(m_X11Display);
}

void Window_X11::SetCaption(const nb::System::String &caption)
{
	int x = XStoreName(m_X11Display, m_X11WindowID, caption.ToUtf8().GetData());
	if(x == 0)
		NB_THROW_EXCEPTION("fail in function [SetCaption]");
}

nb::System::String Window_X11::GetCaption() const
{
	char *pName = new char[80];
	memset(pName, 0, 80);
	Status x = XFetchName(m_X11Display, m_X11WindowID, &pName);
	if(x == 0 || pName == NULL)
		return "";
	else
		return nb::System::String::FromUtf8(pName);
}

void Window_X11::SetRect(const nb::System::RectI &rect)
{
	if(rect == m_rect)
		return;

	XMoveResizeWindow(m_X11Display, m_X11WindowID, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
	m_rect = rect;
}

nb::System::RectI Window_X11::GetRect() const
{
//	XWindowAttributes attrs;
//	XGetWindowAttributes(m_X11Display, m_X11WindowID, &attrs);
	return m_rect;
}

long Window_X11::GetWindowHandle()
{
	return m_X11WindowID;
}

void Window_X11::Pending()
{
	if(!XPending(m_X11Display))
		return;

	XEvent event;
	XNextEvent(m_X11Display, &event);
	switch(event.type)
	{
	case CreateNotify:
		if(m_pW->GetListener())
			m_pW->GetListener()->OnPrimaryAction(WindowEvent::PrimaryAction_Create);
		break;
	case DestroyNotify:
		if(m_pW->GetListener())
			m_pW->GetListener()->OnPrimaryAction(WindowEvent::PrimaryAction_Destroy);
		break;
	case ConfigureNotify:
		if(m_pW->GetListener())
		{
			if(m_rect.GetWidth() != event.xconfigure.width || m_rect.GetHeight() != event.xconfigure.height)
			{
				m_rect.Reset(event.xconfigure.x, event.xconfigure.y, event.xconfigure.width, event.xconfigure.height);
				m_pW->GetListener()->OnResize(event.xconfigure.width, event.xconfigure.height);
			}
		}
		break;
	case ButtonPress:
		if(m_pW->GetListener())
			m_pW->GetListener()->OnPointerAction(WindowEvent::PointerAction_Down, event.xbutton.x, event.xbutton.y);
		break;
	case MotionNotify:
		if(m_pW->GetListener())
			m_pW->GetListener()->OnPointerAction(WindowEvent::PointerAction_Move, event.xmotion.x, event.xmotion.y);
		break;
	case ButtonRelease:
		if(m_pW->GetListener())
		{
			m_pW->GetListener()->OnPointerAction(WindowEvent::PointerAction_Up, event.xbutton.x, event.xbutton.y);
			if(event.xbutton.x >= 0 && event.xbutton.x <= m_rect.GetWidth() && event.xbutton.y >= 0 && event.xbutton.y <= m_rect.GetHeight())
				m_pW->GetListener()->OnPointerAction(WindowEvent::PointerAction_Click, event.xbutton.x, event.xbutton.y);
		}
		break;
	case KeyPress:
		if(m_pW->GetListener())
			m_pW->GetListener()->OnKeyAction(WindowEvent::KeyAction_Down, NativeKeyToKeycode(event.xkey.keycode), 0);
		break;
	case KeyRelease:
		if(m_pW->GetListener())
			m_pW->GetListener()->OnKeyAction(WindowEvent::KeyAction_Up, NativeKeyToKeycode(event.xkey.keycode), 0);
		break;
	default:
		break;
	}
}

WindowEvent::KeyCode Window_X11::NativeKeyToKeycode(int key)
{
	WindowEvent::KeyCode ret = WindowEvent::VKey_Unknown;
	switch(key)
	{
	case 9:
		ret = WindowEvent::VKey_Esc;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	//	ret = WindowEvent::KeyCode(key - (10 - WindowEvent::VKey_1));	//1-0
		break;
	case 67:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
		ret = WindowEvent::KeyCode(key - 67 + WindowEvent::VKey_F1);
		break;
	case 95:
	case 96:
		ret = WindowEvent::KeyCode(key - 95 + WindowEvent::VKey_F11);
		break;
	default:
		break;
	}
}

#endif
