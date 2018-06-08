#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11
#include <X11/X.h>
#include <X11/Xlib.h>
#include "NativeWindow.h"
#include "system/WindowEvent.h"

namespace nb{ namespace System{

class Window;
class Window_X11 : public NativeWindow
{
public:
	Window_X11(Window *pW);
	~Window_X11();

	virtual void SetCaption(const nb::System::String &caption);
	virtual nb::System::String GetCaption() const;

	virtual void SetRect(const nb::System::RectI &rect);
	virtual nb::System::RectI GetRect() const;

	virtual long GetWindowHandle();

	virtual void Pending();

private:
	WindowEvent::KeyCode NativeKeyToKeycode(int key);
	
	::Display			*m_X11Display;
	::Window			m_X11WindowID;
	nb::System::RectI	m_rect;
};

}}

#endif
