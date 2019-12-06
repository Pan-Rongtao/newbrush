#pragma once
#include <vector>
#include "../core/Def.h"

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
	gui::Window * operator[](size_t index);

private:
	std::vector<gui::Window *>	m_windows;
};

}