#include "RangeBase.h"
#include "gui/Grid.h"
#include "core/TypesPropertyValuesStore.h"

using namespace nb::Gui;

using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(RangeBase, UseControl, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(RangeBase, Value, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(RangeBase, Maximum, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(RangeBase, Minimum, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(RangeBase, LargeChange, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(RangeBase, SmallChange, aFloat, NULL);


RangeBase::RangeBase()
: UseControl(new Grid)
{
	ValueChangedEvent.Add(this, &RangeBase::OnValueChangedEvent);
	MaximumChangedEvent.Add(this, &RangeBase::OnMaximumChangedEvent);
	MinimumChangedEvent.Add(this, &RangeBase::OnMinimumChangedEvent);
}

RangeBase::~RangeBase()
{
}

void RangeBase::OnValueChangedEvent(ValueChangedEventParam &param)
{
	OnValueChanged(param.m_fOldValue, param.m_fNewValue);
}

void RangeBase::OnMaximumChangedEvent(ValueChangedEventParam &param)
{
	OnMaximumChanged(param.m_fOldValue, param.m_fNewValue);
}

void RangeBase::OnMinimumChangedEvent(ValueChangedEventParam &param)
{
	OnMinimumChanged(param.m_fOldValue, param.m_fNewValue);
}

void RangeBase::OnValueChanged(float fOldValue, float fNewValue)
{
}

void RangeBase::OnMaximumChanged(float fOldValue, float fNewValue)
{
}

void RangeBase::OnMinimumChanged(float fOldValue, float fNewValue)
{
}
