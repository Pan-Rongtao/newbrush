#include "newbrush/gui/Trigger.h"

using namespace nb;
using namespace nb::gui;

Condition::Condition()
	: Condition(DependencyProperty::invalidProperty(), Var(), nullptr)
{
}

Condition::Condition(const DependencyProperty & dp, const Var & v)
	: Condition(dp, v, nullptr)
{
}

Condition::Condition(const DependencyProperty & dp, const Var & v, BindingPtr bd)
	: property(dp)
	, value(v)
	, binding(bd)
{
}

Trigger::Trigger()
	: Trigger(DependencyProperty::invalidProperty(), Var())
{
}

Trigger::Trigger(const DependencyProperty & dp, const Var & v)
	: property(dp)
	, value(v)
{
}
