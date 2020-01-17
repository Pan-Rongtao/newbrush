#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/TextBlock.h"

using namespace nb;
using namespace nb::gui;

class TestTextBlock : public TestBase
{
public:
	void test();

private:
//	void onStateChanged(const Timeline::StateChangedArgs &args);
//	void onProgress(const Timeline::ProgressArgs &args);
//	void onCompleted(const Timeline::CompleteArgs &args);

	std::shared_ptr<TextBlock>			m_text;
	std::shared_ptr<nb::gui::Window>	m_window;
};