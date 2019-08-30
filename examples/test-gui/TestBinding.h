#pragma once
#include "../TestBase.h"
#include "gui/Binding.h"
#include "gui/BindingMaster.h"
#include "gui/DataContext.h"
#include "gui/TextBlock.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gui;

class TestBinding : public TestBase
{
public:
	void test();

	std::shared_ptr<gui::Window>	m_window;
	std::shared_ptr<TextBlock>	m_text;
	ObjectDataPtr				m_dataRoot;
};