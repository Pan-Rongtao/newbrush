#pragma once
#include "../gui/Control.h"
#include "../core/Event.h"

namespace nb{ namespace gui {

class NB_API RangeBase : public Control
{
public:
	RangeBase();
	virtual ~RangeBase();

public:/*
	Property_rw<float>			Value;
	Property_rw<float>			Maximum;
	Property_rw<float>			Minimum;
	Property_rw<float>			SmallChange;
	Property_rw<float>			LargeChange;*/
			
protected:
	virtual void OnValueChanged(float fOldValue, float fNewValue);
	virtual void OnMaximumChanged(float fOldValue, float fNewValue);
	virtual void OnMinimumChanged(float fOldValue, float fNewValue);

};

}}
