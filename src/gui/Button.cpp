#include "newbrush/gui/Button.h"

using namespace nb;

Button::Button()
{
}

DependencyProperty Button::IsCancelProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsCancel", false);
	return dp;
}

DependencyProperty Button::IsDefaultProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsDefault", false);
	return dp;
}

