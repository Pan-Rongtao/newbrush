#include "newbrush/gui/Setter.h"
#include "newbrush/gui/UIElement.h"

using namespace nb;
using namespace nb::gui;

void SetterBase::attach(UIElement* uie)
{
}

Setter::Setter()
	: Setter(DependencyProperty::invalidProperty(), Var())
{
}

Setter::Setter(const DependencyProperty & dp, const Var & v)
	: property(dp)
	, value(v)
{
}

void Setter::attach(UIElement* uie)
{
	uie->setValue(property, value);
}

void EventSetter::attach(UIElement* uie)
{
	uie->addHandler(event, handler);
}
