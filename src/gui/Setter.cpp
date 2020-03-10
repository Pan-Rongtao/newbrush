#include "newbrush/gui/Setter.h"
#include "newbrush/gui/UIElement.h"

using namespace nb;

void SetterBase::attach(UIElement* uie)
{
}

Setter::Setter()
	: Setter(DependencyProperty::invalidProperty(), Var(), "")
{
}

Setter::Setter(const DependencyProperty & dp, const Var & v)
	: Setter(DependencyProperty::invalidProperty(), v, "")
{
}

Setter::Setter(const DependencyProperty &dp, const Var &v, const std::string &_targetName)
	: property(dp)
	, value(v)
	, targetName(_targetName)
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
