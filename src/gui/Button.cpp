#include "newbrush/gui/Button.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Button::Button()
{
}

DependencyPropertyPtr Button::IsCancelProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsCancel", false, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Button::IsDefaultProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsDefault", false, nullptr, nullptr, nullptr);
	return dp;
}
