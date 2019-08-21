#pragma once
#include "../TestBase.h"
#include "gui/Window.h"
#include "gui/PropertyAnimation.h"
#include "gui/Timeline.h"
#include "core/Timer.h"

using namespace nb;
using namespace nb::gui;

class TestWindow :public nb::gui::Window, public TestBase
{
public:
	virtual void test();

	PropertyAnimation<float>	doubleAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);

	void onTick(const Timer::TickArgs &args);

	Timer m_timer;
};
