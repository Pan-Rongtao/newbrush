#include "gui/Button.h"

using namespace nb::gui;

Button::Button()
	: IsCancel([&](bool v) { set(IsCancelProperty(), v); }, [&]() {return get<bool>(IsCancelProperty()); })
	, IsDefault([&](bool v) { set(IsDefaultProperty(), v); }, [&]() {return get<bool>(IsDefaultProperty()); })
{
}

const DependencyProperty Button::IsCancelProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Button, bool>("IsCancel");
	return dp;
}

const DependencyProperty Button::IsDefaultProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Button, bool>("IsDefault");
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
