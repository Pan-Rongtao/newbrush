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

	std::shared_ptr<Window>		m_window;
	std::shared_ptr<UIElement>	m_text;
	std::shared_ptr<DataObject>	m_dataRoot;
};