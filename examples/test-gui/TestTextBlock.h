#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/TextBlock.h"
#include "gui/PropertyAnimation.h"

using namespace nb::core;
using namespace nb::gui;

class TestTextBlock : public TestBase
{
public:
	void test();

	ColorAnimation				colorAni;

private:
private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);

	Window	m_window;
};