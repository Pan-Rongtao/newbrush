#include "newbrush/gui/Setter.h"

using namespace nb;
using namespace nb::gui;

Setter::Setter()
	: Setter(DependencyProperty::invalidProperty(), Var())
{
}

Setter::Setter(const DependencyProperty & dp, const Var & v)
	: property(dp)
	, value(v)
{
}
