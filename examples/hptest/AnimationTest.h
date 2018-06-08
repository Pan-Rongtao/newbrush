#pragma once

#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/Storyboard.h"
#include "../../../Include/Gui/Rectangle.h"

namespace nb
{
//using namespace Gui;
}

class AnimationTest : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	AnimationTest(void);
	virtual ~AnimationTest(void);
	void Run();

	nb::System::TimerPtr m_timer1;
	nb::System::TimerPtr m_timer2;

	nb::Media::Storyboard m_storyboard;
	nb::Gui::Rectangle *m_rect;

	void OnTimerOut(nb::System::Timer::TimeoutParam &param);

//	NB_OBJECT_PROPERTY_DECLARE(a, Float)

};
