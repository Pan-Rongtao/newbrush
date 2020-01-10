#pragma once
#include "../TestBase.h"
#include "gui/UIElement.h"

using namespace nb::gui;

class TestUIElement : public TestBase
{
public:
	void test();

	std::shared_ptr<UIElement>	m_uielement;
};