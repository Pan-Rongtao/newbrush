#pragma once
#include "../TestBase.h"
#include "gui/PropertyAnimationUsingKeyFrames.h"

using namespace nb;
using namespace nb::gui;

class TestPropertyAnimationUsingKeyFrames : public TestBase
{
public:
	void test();

	TestPropertyAnimationUsingKeyFrames();

	Property_rw<double>						Width;
	double									m_w;
	PropertyAnimationUsingKeyFrames<double>	doubleAni;

private:
	void onStateChanged(const Timeline::StateChangedArgs &args);
	void onProgress(const Timeline::ProgressArgs &args);
	void onCompleted(const Timeline::CompleteArgs &args);
};