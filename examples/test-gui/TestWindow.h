#pragma once
#include "../TestBase.h"
#include "gui/Window.h"

class TestWindow :public nb::gui::Window, public TestBase
{
public:
	virtual void test();

};
