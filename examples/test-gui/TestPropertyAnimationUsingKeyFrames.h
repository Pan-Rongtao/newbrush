#pragma once
#include "../TestBase.h"
#include "gui/PropertyAnimationUsingKeyFrames.h"

using namespace nb::core;
using namespace nb::gui;

class TestPropertyAnimationUsingKeyFrames : public TestBase
{
public:
	void test();

	TestPropertyAnimationUsingKeyFrames();

	Property_rw<double>						Width;
	PropertyAnimationUsingKeyFrames<double>	doubleAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);
};