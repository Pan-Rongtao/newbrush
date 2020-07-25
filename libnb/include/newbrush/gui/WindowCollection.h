#pragma once
#include <vector>
#include "newbrush/core/Event.h"

namespace nb {

class Window;
class WindowCollection
{
public:
	void push(Window *w);
	void erase(Window *w);
	std::vector<Window *> &windows();

	void setMainWindow(Window *w);
	Window *mainWindow();

	struct WindowClosedEventArgs	{ bool isMain; };
	Event<WindowClosedEventArgs>	WindowClosed;
	struct WindowFocusEventArgs		{ bool focused; };
	Event<WindowFocusEventArgs>		WindowFocus;

private:
	std::vector<Window *>	m_windows;
	Window					*m_mainWindow;
};

}