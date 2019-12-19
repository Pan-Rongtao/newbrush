#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/Grid.h"
#include "media/PropertyAnimation.h"

using namespace nb::gui;
class TestGrid : public TestBase
{
public:
	virtual void test() override;

	PropertyAnimation<float>	doubleAni;
	std::shared_ptr<nb::gui::Window> m_window;
};