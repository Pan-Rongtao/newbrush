#include "newbrush/gui/Trigger.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/core/DataContext.h"

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

bool Trigger::match(const DependencyProperty & dp, const Var & v) const
{
	return dp == property && v == value;
}

void TriggerBase::processSetters(UIElement *uie, std::vector<SetterBasePtr> setters)
{
	for (auto setterBase : setters)
	{
		auto setter = std::dynamic_pointer_cast<Setter>(setterBase);
		if (setter)
		{
			uie->set(setter->property, setter->value);
		}
		else
		{
			auto eventSetter = std::dynamic_pointer_cast<EventSetter>(setterBase);
			if (!eventSetter)
				nbThrowException(std::runtime_error, "unsupported SetterBase subclass in style setter [%s]", typeid(setterBase).name());
			uie->addHandler(eventSetter->event, eventSetter->handler);
		}
	}
}

bool MultiTrigger::match(UIElement * uie) const
{
	for (auto const &c : conditions)
	{
		if (uie->get(c.property) != c.value)
			return false;
	}
	return true;
}

bool DataTrigger::match(const Var & v) const
{
	return v == value;
}

bool MultiDataTrigger::match(const Var & v) const
{
	for (auto const &c : conditions)
	{
		if (v != c.value)
			return false;
	}
	return true;
}
