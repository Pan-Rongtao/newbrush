#include "gui/RangeBase.h"

using namespace nb::gui;
using namespace nb::core;

RangeBase::RangeBase()
	: Value(nullptr, nullptr)
	, Maximum(nullptr, nullptr)
	, Minimum(nullptr, nullptr)
	, SmallChange(nullptr, nullptr)
	, LargeChange(nullptr, nullptr)
{
}

RangeBase::~RangeBase()
{
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
