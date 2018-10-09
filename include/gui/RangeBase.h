#pragma once
#include "../gui/Control.h"
#include "../core/Event.h"

namespace nb{ namespace gui {

class NB_API RangeBase : public Control
{
public:
	RangeBase();
	virtual ~RangeBase();

public:
	nb::core::Property_rw<double>			Value;
	nb::core::Property_rw<double>			Maximum;
	nb::core::Property_rw<double>			Minimum;
	nb::core::Property_rw<double>			SmallChange;
	nb::core::Property_rw<double>			LargeChange;
			
protected:
	virtual void OnValueChanged(float fOldValue, float fNewValue);
	virtual void OnMaximumChanged(float fOldValue, float fNewValue);
	virtual void OnMinimumChanged(float fOldValue, float fNewValue);

};

}}
