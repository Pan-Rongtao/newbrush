#include "gui/Button.h"

using namespace nb::gui;

Button::Button()
	: IsCancel([&](bool v) { set(IsCancelProperty(), v); }, [&]() {return get<bool>(IsCancelProperty()); })
	, IsDefault([&](bool v) { set(IsDefaultProperty(), v); }, [&]() {return get<bool>(IsDefaultProperty()); })
{
}

DependencyProperty Button::IsCancelProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsCancel");
	return dp;
}

DependencyProperty Button::IsDefaultProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsDefault");
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
