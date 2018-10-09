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
	nb::core::Property_rw<int>		Delay;
	nb::core::Property_rw<int>		Interval;
	
private:
	nb::core::Timer	m_timer;
};

}}

