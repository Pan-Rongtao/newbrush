#include "../TestBase.h"
#include "gui/Canvas.h"
#include "gui/Window.h"
#include "gui/Rectangle.h"
#include "gui/Rectangle.h"

using namespace nb::core;
using namespace nb::gui;

class TestCanvas : public TestBase
{
public:
	void test();

	Window m_window;
};