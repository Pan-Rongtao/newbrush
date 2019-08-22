#include "gui/ButtonBase.h"

using namespace nb::gui;

ButtonBase::ButtonBase()
	: ClickMode([&](ClickModeE v) {set(ClickModeProperty(), v); }, [&]() {return get<ClickModeE>(ClickModeProperty()); })
	, IsPressed([&]() {return get<bool>(IsPressedProperty()); })
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
	if (IsPressed())
	{
		Click.dispatch({});
		set(IsPressedProperty(), false);
	}
}
