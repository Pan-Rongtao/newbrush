#pragma once
#include "../TestBase.h"
#include "gui/Application.h"
#include "TestWindow.h"

class TestApp : public nb::gui::Application, public TestBase
{
public:
	virtual void test();

private:
};
