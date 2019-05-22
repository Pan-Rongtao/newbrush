#pragma once
#include "../TestBase.h"
#include "core/Point.h"
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

	Property_rw<Point>			Position;
	PropertyAnimation<Point>		piontAni;

	Property_rw<Color>			Background;
	ColorAnimation				colorAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);
};