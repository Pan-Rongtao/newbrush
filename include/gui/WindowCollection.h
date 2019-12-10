#pragma once
#include <vector>
#include "../core/Event.h"
#include "../core/EventArgs.h"

namespace nb {
namespace gui{
	class Window;
}
}

namespace nb {

class WindowCollection
{
public:
	void push(gui::Window *w);
	void erase(gui::Window *w);
	std::vector<gui::Window *> &windows();

	void setMainWindow(gui::Window *w);
	gui::Window *mainWindow();

	struct WindowClosedEventArgs	{ bool isMain; };
	Event<WindowClosedEventArgs>	WindowClosed;
	struct WindowFocusEventArgs		{ bool focused; };
	Event<WindowFocusEventArgs>		WindowFocus;

private:
	std::vector<gui::Window *>	m_windows;
	gui::Window					*m_mainWindow;
};

}