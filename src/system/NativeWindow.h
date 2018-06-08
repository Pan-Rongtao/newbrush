#pragma once
#include <map>
#include "system/String.h"
#include "system/RectI.h"
#include "system/WindowEvent.h"

namespace nb{ namespace System{

class Window;
class WindowEvent;
class NativeWindow
{
public:
	virtual void SetCaption(const nb::System::String &caption) = 0;
	virtual nb::System::String GetCaption() const = 0;

	virtual void SetRect(const nb::System::RectI &rect) = 0;
	virtual nb::System::RectI GetRect() const = 0;

	virtual long GetWindowHandle() = 0;

	virtual void Pending() = 0;

	virtual ~NativeWindow();

protected:
	NativeWindow(Window *pW);

	static void OnPrimaryAction(Window *pW, WindowEvent::PrimaryAction action);
	static void OnResize(Window *pW, int width, int height);
	static void OnKeyAction(Window *pW, WindowEvent::KeyAction action, WindowEvent::KeyCode key, int mask);
	static void OnPointerAction(Window *pW, WindowEvent::PointerAction action, int x, int y);

	Window										*m_pW;
	static std::map<long, Window *>				m_mapInternals;
private:
	NativeWindow(const NativeWindow &other);
	void operator = (const NativeWindow &other);
};

}}
