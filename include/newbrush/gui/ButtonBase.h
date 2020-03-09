#pragma once
#include "newbrush/gui/ContentControl.h"

namespace nb{

enum class ClickModeE
{
	hover,	//鼠标悬停在控件上时引发click事件
	press,	//压下时引发click事件
	release,//压下和释放按钮时引发click事件
};

class NB_API ButtonBase : public ContentControl
{
public:
	virtual ~ButtonBase() = default;

	static DependencyProperty	ClickModeProperty();	//点击模式的依赖属性（默认为ClickModeE::release)
	static DependencyProperty	IsPressedProperty();	//是否压下的依赖属性

	Event<RoutedEventArgs>		Click;					//点击事件
	static RoutedEvent			ClickEvent();			//点击路由事件(RoutedEventArgs)

	virtual void onIsPressedChanged(const DependencyPropertyChangedEventArgs &args);

protected:
	ButtonBase();

	virtual bool isEnableCore();						//重载以返回子类的可用状态

	virtual void onClick();
	virtual void onMouseEnter(const MouseEventArgs &args) override;
	virtual void onMouseLeave(const MouseEventArgs &args) override;
	virtual void onMouseMove(const MouseEventArgs &args) override;
	virtual void onMouseLeftButtonDown(const MouseButtonEventArgs &args) override;
	virtual void onMouseLeftButtonUp(const MouseButtonEventArgs &args) override;

private:
	void updateIsPress();
};

}