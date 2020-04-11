#include "newbrush/gui/RangeBase.h"

using namespace nb;

RangeBase::RangeBase()
{
}

RangeBase::~RangeBase()
{
}

DependencyProperty RangeBase::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<RangeBase, float>("Value", 0.0f, onValuePropertyChanged, coerceValue);
	return dp;
}

DependencyProperty RangeBase::MaximumProperty()
{
	static auto dp = DependencyProperty::registerDependency<RangeBase, float>("Maximum", 0.0f, onMaxinumPropertyChanged, coerceMaximum);
	return dp;
}

DependencyProperty RangeBase::MinimumProperty()
{
	static auto dp = DependencyProperty::registerDependency<RangeBase, float>("Minimum", 0.0f, onMinimumPropertyChanged, coerceMinimum);
	return dp;
}

DependencyProperty RangeBase::SmallChangeProperty()
{
	static auto dp = DependencyProperty::registerDependency<RangeBase, float>("SmallChange", 0.0f);
	return dp;
}

DependencyProperty RangeBase::LargeChangeProperty()
{
	static auto dp = DependencyProperty::registerDependency<RangeBase, float>("LargeChange", 0.0f);
	return dp;
}

void RangeBase::onValueChanged(float oldValue, float newValue)
{
	RoutedProperyChangedEventArgs e;
	e.oldValue = oldValue;
	e.newValue = newValue;
	ValueChanged.invoke(e);
}

void RangeBase::onMaxinumChanged(float oldValue, float newValue)
{
}

void RangeBase::onMininumChanged(float oldValue, float newValue)
{
}

Var RangeBase::coerceValue(DependencyObject * d, Var baseValue)
{
	auto self = dynamic_cast<RangeBase *>(d);
	auto min = self->getValue<float>(MinimumProperty());
	auto max = self->getValue<float>(MaximumProperty());
	return nb::clamp<float>(min, max, (float)baseValue);
}

Var RangeBase::coerceMaximum(DependencyObject * d, Var baseValue)
{
	auto self = dynamic_cast<RangeBase *>(d);
	auto min = self->getValue<float>(MinimumProperty());
	return baseValue < min ? min : baseValue;
}

Var RangeBase::coerceMinimum(DependencyObject * d, Var baseValue)
{
	auto self = dynamic_cast<RangeBase *>(d);
	auto max = self->getValue<float>(MaximumProperty());
	return baseValue > max ? max : baseValue;
}

void RangeBase::onValuePropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
	auto self = dynamic_cast<RangeBase *>(d);
	self->onMaxinumChanged(e->oldValue.extract<float>(), e->newValue.extract<float>());
}

void RangeBase::onMaxinumPropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
	auto self = dynamic_cast<RangeBase *>(d);
	auto max = e->newValue.extract<float>();
	auto value = self->getValue<float>(ValueProperty());
	if (value > max)
	{
		self->setValue(ValueProperty(), max);
	}
	self->onMaxinumChanged(e->oldValue.extract<float>(), max);
}

void RangeBase::onMinimumPropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
	auto self = dynamic_cast<RangeBase *>(d);
	auto min = e->newValue.extract<float>();
	auto value = self->getValue<float>(ValueProperty());
	if (value < min)
	{
		self->setValue(ValueProperty(), min);
	}
	self->onMaxinumChanged(e->oldValue.extract<float>(), min);
}
