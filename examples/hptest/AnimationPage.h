#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/Storyboard.h"
#include "../../../Include/Gui/Rectangle.h"

class AnimationPage : public nb::Gui::Page
{
public:
	AnimationPage(void);
	virtual ~AnimationPage(void);

	nb::Media::Storyboard m_storyboard;
	nb::Gui::Rectangle *m_rect;

};
