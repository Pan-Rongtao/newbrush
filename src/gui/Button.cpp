#include "gui/Button.h"

using namespace nb::gui;

Button::Button()
	: IsCancel([&](bool v) { set(IsCancelProperty(), v); }, [&]()->bool& {return get<bool>(IsCancelProperty()); })
	, IsDefault([&](bool v) { set(IsDefaultProperty(), v); }, [&]()->bool& {return get<bool>(IsDefaultProperty()); })
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

void Button::onMouseDown()
{
}

void Button::onMouseUp()
{
}

void Button::onMouseLeftButtonDown()
{

}

void Button::onMouseLeftButtonUp()
{
}
