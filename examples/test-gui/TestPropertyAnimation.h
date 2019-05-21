#pragma once
#include "../TestBase.h"
#include "core/Color.h"
#include "gui/PropertyAnimation.h"

using namespace nb::core;
using namespace nb::gui;

class TestPropertyAnimation : public TestBase
{
public:
	void test();

	Property_rw<double>			Width;
	PropertyAnimation<double>	doubleAni;

	Property_rw<Color>			Background;
	PropertyAnimation<Color>	colorAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);
};