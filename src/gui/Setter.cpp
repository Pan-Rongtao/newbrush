#include "newbrush/gui/Setter.h"
#include "newbrush/gui/UIElement.h"

using namespace nb;

void SetterBase::attach(UIElement* uie)
{
}

Setter::Setter()
	: property(DependencyProperty::invalidProperty())
{
}

Setter::Setter(const DependencyProperty & dp, const Var & v)
	: property(dp)
	, value(v)
{
}

Setter::Setter(const DependencyProperty &dp, const Var &v, const std::string &_targetName)
	: property(dp)
	, value(v)
	, targetName(std::make_shared<std::string>(_targetName))
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
