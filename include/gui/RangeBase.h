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
	nb::core::Property_rw<float>			Value;
	nb::core::Property_rw<float>			Maximum;
	nb::core::Property_rw<float>			Minimum;
	nb::core::Property_rw<float>			SmallChange;
	nb::core::Property_rw<float>			LargeChange;
			
protected:
	virtual void OnValueChanged(float fOldValue, float fNewValue);
	virtual void OnMaximumChanged(float fOldValue, float fNewValue);
	virtual void OnMinimumChanged(float fOldValue, float fNewValue);

};

}}
