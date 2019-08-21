#pragma once
#include "gui/Button.h"
#include "core/Timer.h"

namespace nb{ namespace gui {

class NB_API RepeatButton : public Button
{
public:
	RepeatButton();
	virtual ~RepeatButton();

public:
	Property_rw<int>		Delay;
	Property_rw<int>		Interval;
	
private:
	Timer	m_timer;
};

}}

