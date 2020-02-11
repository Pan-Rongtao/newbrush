#pragma once
#include "newbrush/gui/Button.h"
#include "newbrush/core/Timer.h"

namespace nb{ namespace gui {

class NB_API RepeatButton : public Button
{
public:
	RepeatButton();
	virtual ~RepeatButton();
	/*
	Property_rw<int>		Delay;
	Property_rw<int>		Interval;*/
	
private:
	Timer	m_timer;
};

}}

