#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
#include <Windows.h>
#include <WindowsX.h>
#include "NativeWindow.h"
#include "system/RectI.h"

namespace nb{ namespace System{

class Window;
class Window_Win32 : public NativeWindow
{
public:
	Window_Win32(Window *pV);
	~Window_Win32();

	virtual void SetCaption(const nb::System::String &caption);
	virtual nb::System::String GetCaption() const;

	virtual void SetRect(const nb::System::RectI &rect);
	virtual nb::System::RectI GetRect() const;

	virtual long GetWindowHandle();

	virtual void Pending();

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HINSTANCE		m_Instance;
	HWND			m_Hwnd;
	static bool		m_bPressed;
};

}}
#endif
