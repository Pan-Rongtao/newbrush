#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/TextBlock.h"
#include "gui/PropertyAnimation.h"

using namespace nb::core;
using namespace nb::media;
using namespace nb::gui;

class TestTextBlock : public TestBase
{
public:
	void test();

	ColorAnimation				colorAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);

	std::shared_ptr<TextBlock>	m_text;
	nb::gui::Window				m_window;
};