#include "gui/ButtonBase.h"

using namespace nb;
using namespace nb::gui;

ButtonBase::ButtonBase()
{
}

bool ButtonBase::isEnableCore()
{
	return true;
}

DependencyProperty ButtonBase::ClickModeProperty()
{
	static auto dp = DependencyProperty::registerDependency<ButtonBase, ClickModeE>("ClickMode", ClickModeE::release);
	return dp;
}

DependencyProperty ButtonBase::IsPressedProperty()
{
	static auto dp = DependencyProperty::registerDependency<ButtonBase, bool>("IsPressed", false);
	return dp;
}

void ButtonBase::onClick()
{
}

void ButtonBase::onKeyDown()
{
}

void ButtonBase::onKeyUp()
{
}

void ButtonBase::onMouseEnter()
{
}

void ButtonBase::onMouseMove()
{
}

void ButtonBase::onMouseLeave()
{
}

void ButtonBase::onLeftButtonDown()
{
	set(IsPressedProperty(), true);
}

void ButtonBase::onLeftButtonUp()
{
	auto pressed = get<bool>(IsPressedProperty());
	if (pressed)
	{
		Click.invoke({});
		set(IsPressedProperty(), false);
	}
}
