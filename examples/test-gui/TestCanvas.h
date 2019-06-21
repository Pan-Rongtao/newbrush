#include "../TestBase.h"
#include "gui/Canvas.h"
#include "gui/Window.h"
#include "gui/Rectangle.h"
#include "gui/PropertyAnimation.h"

using namespace nb::core;
using namespace nb::gui;

class TestCanvas : public TestBase
{
public:
	void test();


	PropertyAnimation<double>	doubleAni;
	nb::gui::Window m_window;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);
};