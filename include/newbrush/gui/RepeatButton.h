#pragma once
#include "newbrush/gui/Button.h"
#include "newbrush/core/Timer.h"

namespace nb{

class NB_API RepeatButton : public Button
{
	RTTR_ENABLE(Button)
public:
	RepeatButton();
	virtual ~RepeatButton();

	static DependencyPropertyPtr DelayProperty();	//是否是“取消”按钮依赖属性，用户可以通过按ESC键激活“取消”按钮
	static DependencyPropertyPtr IntervalProperty();	//是否是“默认”按钮依赖属性，用户可以通过按Enter键激活“默认”按钮

	/*
	Property_rw<int>		Delay;
	Property_rw<int>		Interval;*/
	
protected:
	virtual void onClick();
	virtual void onMouseEnter(const MouseEventArgs &args) override;
	virtual void onMouseLeave(const MouseEventArgs &args) override;
	virtual void onMouseLeftButtonDown(const MouseButtonEventArgs &args) override;
	virtual void onMouseLeftButtonUp(const MouseButtonEventArgs &args) override;

private:
	void onTick(const EventArgs &e);

	static void onDelayPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);
	static void onIntervalPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	Timer		m_timer;
	uint64_t	m_startTicks;
};

}
