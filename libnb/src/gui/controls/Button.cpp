#include "newbrush/gui/controls/Button.h"

using namespace nb;

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
