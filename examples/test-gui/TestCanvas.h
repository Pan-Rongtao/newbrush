#include "../TestBase.h"
#include "gui/Canvas.h"
#include "gui/Window.h"
#include "gui/Shape.h"

using namespace nb;
using namespace nb::gui;

class TestCanvas : public TestBase
{
public:
	void test();


	std::shared_ptr<nb::gui::Window> m_window;

private:
	void onStateChanged(const EventArgs &args);
	void onProgress(const EventArgs &args);
	void onCompleted(const EventArgs &args);
};