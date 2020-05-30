#include "newbrush/gui/RepeatButton.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

RepeatButton::RepeatButton()
{
	m_timer.Tick += std::bind(&RepeatButton::onTick, this, std::placeholders::_1);
}

RepeatButton::~RepeatButton()
{
}

DependencyProperty RepeatButton::DelayProperty()
{
	static auto dp = DependencyProperty::registerDependency<RepeatButton, uint32_t>("Delay", 500, onDelayPropertyChanged);
	return dp;
}

DependencyProperty RepeatButton::IntervalProperty()
{
	static auto dp = DependencyProperty::registerDependency<RepeatButton, uint32_t>("Interval", 33, onIntervalPropertyChanged);
	return dp;
}

void RepeatButton::onClick()
{
	ButtonBase::onClick();
}

void RepeatButton::onMouseEnter(const MouseEventArgs & args)
{
	ButtonBase::onMouseEnter(args);
}

void RepeatButton::onMouseLeave(const MouseEventArgs & args)
{
	ButtonBase::onMouseLeave(args);
}

void RepeatButton::onMouseLeftButtonDown(const MouseButtonEventArgs & args)
{
	ButtonBase::onMouseLeftButtonDown(args);
	auto interval = getValue<uint32_t>(IntervalProperty());
	m_timer.start(interval);
	m_startTicks = nb::getTickCount();
}

void RepeatButton::onMouseLeftButtonUp(const MouseButtonEventArgs & args)
{
	ButtonBase::onMouseLeftButtonUp(args);
	m_timer.stop();
}

void RepeatButton::onTick(const EventArgs & e)
{
	auto delay = getValue<uint32_t>(DelayProperty());
	auto curTicks = nb::getTickCount();
	if (curTicks - m_startTicks < delay)
	{
		return;
	}

	auto isPressed = getValue<bool>(IsPressedProperty());
	if (isPressed)
	{
		onClick();
	}
}

void RepeatButton::onDelayPropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
}

void RepeatButton::onIntervalPropertyChanged(DependencyObject * d, DependencyPropertyChangedEventArgs * e)
{
	auto self = dynamic_cast<RepeatButton*>(d);
	self->m_timer.setInterval(e->newValue.get_value<uint32_t>());
}

std::shared_ptr<MetaObject> RepeatButton::getMetaObject()
{
	auto meta = MetaObject::get<RepeatButton, Button>("内容控件", "RepeatButton", "重复触发按钮，按钮的一种，可重复发出点击事件。", [] {return std::make_shared<RepeatButton>(); });
	return meta;
}
