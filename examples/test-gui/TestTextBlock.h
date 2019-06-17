#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/TextBlock.h"

using namespace nb::gui;

class TestTextBlock : public TestBase
{
public:
	void test();

private:
	Window	m_window;
};