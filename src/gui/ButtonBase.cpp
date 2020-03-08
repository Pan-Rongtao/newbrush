#include "newbrush/gui/ButtonBase.h"

using namespace nb;

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
	static auto dp = DependencyProperty::registerDependency<ButtonBase, bool>("IsPressed", false, [](DependencyObject *d, DependencyPropertyChangedEventArgs *args) {
		auto ctrl = dynamic_cast<ButtonBase *>(d);
		ctrl->onIsPressedChanged(*args);
	});
	return dp;
}

RoutedEvent ButtonBase::ClickEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<ButtonBase, RoutedEventArgs>("Click", RoutingStrategyE::bubble);
	return e;
}

void ButtonBase::onClick()
{
	auto args = std::make_shared<RoutedEventArgs>(ButtonBase::ClickEvent(), this);
	raiseEvent(args);
}

void ButtonBase::onIsPressedChanged(const DependencyPropertyChangedEventArgs & args)
{
	//
}

void ButtonBase::onMouseEnter(const MouseEventArgs & args)
{
	ContentControl::onMouseEnter(args);
	const_cast<MouseEventArgs &>(args).Handled = true;
}

void ButtonBase::onMouseLeave(const MouseEventArgs & args)
{
	ContentControl::onMouseLeave(args);
	const_cast<MouseEventArgs &>(args).Handled = true;
}

void ButtonBase::onMouseMove(const MouseEventArgs & args)
{
	ContentControl::onMouseMove(args);
	updateIsPress();
	const_cast<MouseEventArgs &>(args).Handled = true;
}

void ButtonBase::onMouseLeftButtonDown(const MouseButtonEventArgs & args)
{
	setValue(IsPressedProperty(), true);
	auto clickMode = getValue<ClickModeE>(ClickModeProperty());
	if (clickMode == ClickModeE::press)
	{
		onClick();
	}
	ContentControl::onMouseLeftButtonDown(args);
}

void ButtonBase::onMouseLeftButtonUp(const MouseButtonEventArgs & args)
{
	auto isPressed = getValue<bool>(IsPressedProperty());
	auto clickMode = getValue<ClickModeE>(ClickModeProperty());
	bool shouldClick = isPressed && clickMode == ClickModeE::release;
	if (shouldClick)
	{
		Click.invoke({});
		setValue(IsPressedProperty(), false);
	}
	ContentControl::onMouseLeftButtonDown(args);
}

void ButtonBase::updateIsPress()
{
}
