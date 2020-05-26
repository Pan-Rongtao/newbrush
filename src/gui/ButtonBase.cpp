#include "newbrush/gui/ButtonBase.h"
#include "newbrush/core/Log.h"
#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

ButtonBase::ButtonBase()
	: m_leaveWithPressed(false)
{
}

bool ButtonBase::isEnableCore()
{
	return true;
}

DependencyProperty ButtonBase::ClickModeProperty()
{
	static auto dp = DependencyProperty::registerDependency<ButtonBase, ClickModeE>("ClickMode", ClickModeE::Release);
	return dp;
}

DependencyProperty ButtonBase::IsPressedProperty()
{
	static auto dp = DependencyProperty::registerDependency<ButtonBase, bool>("IsPressed", false, onIsPressedPropertyChanged);
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
	Click.invoke(*args);
}

void ButtonBase::onIsPressedChanged(const DependencyPropertyChangedEventArgs & args)
{
//	Log::info("ispressed=%d", args.newValue.extract<bool>());
}

void ButtonBase::onMouseEnter(const MouseEventArgs & args)
{
	ContentControl::onMouseEnter(args);
	const_cast<MouseEventArgs &>(args).Handled = true;
	if (m_leaveWithPressed)
	{
		setValue(IsPressedProperty(), true);
	}
//	Log::info("%s", __FUNCTION__);
}

void ButtonBase::onMouseLeave(const MouseEventArgs & args)
{
	ContentControl::onMouseLeave(args);
	const_cast<MouseEventArgs &>(args).Handled = true;
	auto isPressed = getValue<bool>(IsPressedProperty());
	m_leaveWithPressed = isPressed;
	setValue(IsPressedProperty(), false);
//	Log::info("%s", __FUNCTION__);
}

void ButtonBase::onMouseMove(const MouseEventArgs & args)
{
	ContentControl::onMouseMove(args);
	const_cast<MouseEventArgs &>(args).Handled = true;
//	Log::info("%s", __FUNCTION__);
}

void ButtonBase::onMouseLeftButtonDown(const MouseButtonEventArgs & args)
{
	setValue(IsPressedProperty(), true);
	auto clickMode = getValue<ClickModeE>(ClickModeProperty());
	if (clickMode == ClickModeE::Press)
	{
		onClick();
	}
	ContentControl::onMouseLeftButtonDown(args);
//	Log::info("%s", __FUNCTION__);
}

void ButtonBase::onMouseLeftButtonUp(const MouseButtonEventArgs & args)
{
	m_leaveWithPressed = false;
	auto isPressed = getValue<bool>(IsPressedProperty());
	auto clickMode = getValue<ClickModeE>(ClickModeProperty());
	auto w = dynamic_cast<Window*>(getRoot());
	auto pt = w->getMousePosition();
	bool shouldClick = isPressed && clickMode == ClickModeE::Release && hitTestCore(pt);
	if (shouldClick)
	{
		setValue(IsPressedProperty(), false);
		onClick();
	}
	ContentControl::onMouseLeftButtonUp(args);
//	Log::info("%s", __FUNCTION__);
}

void ButtonBase::onIsPressedPropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * args)
{
	auto ctrl = dynamic_cast<ButtonBase *>(d);
	ctrl->onIsPressedChanged(*args);
}

void ButtonBase::updateIsPress()
{
	auto w = dynamic_cast<Window*>(getRoot());
	auto pt = w->getMousePosition();
	auto isHit = hitTestCore(pt);
	auto isPressed = getValue<bool>(IsPressedProperty());
	if (isPressed)
	{
		setValue(IsPressedProperty(), isHit);
	}
	else if (m_leaveWithPressed)
	{
		setValue(IsPressedProperty(), true);
	}
}

std::shared_ptr<MetaObject> ButtonBase::getMetaObject()
{
	auto meta = MetaObject::get<ButtonBase, ContentControl>("形状", "Line", "线段，形状的一种。", [] {return nullptr; });
	meta->addProperty(ClickModeProperty(), "其他", "线段起点的X分量", PropertyDescriptor::Enum, "Hover|Press|Release");
	return meta;
}
