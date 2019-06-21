#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/Rectangle.h"
#include "gui/WrapPanel.h"

using namespace nb::core;
using namespace nb::gui;

class TestWrapPanel : public TestBase
{
public:
	void test();

	nb::gui::Window m_window;
};