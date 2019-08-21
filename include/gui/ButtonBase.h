#pragma once
#include "ContentControl.h"

namespace nb{ 
namespace gui{

enum class ClickModeE
{
	hover,	//鼠标悬停在控件上时引发click事件
	press,	//压下时引发click事件
	release,//压下和释放按钮时引发click事件
};

class ButtonBase : ContentControl
{
public:
	ButtonBase();
	virtual ~ButtonBase() = default;

	//重载以返回子类的可用状态
	virtual bool isEnableCore();


	Property_rw<ClickModeE>			ClickMode;		//指定何种模式引发click的发生
	Property_r<bool>				IsPressed;		//是否处于压下状态

	struct ClickArgs {};
	Event<ClickArgs>				Click;			//点击事件

	static const DependencyProperty	ClickModeProperty();
	static const DependencyProperty	IsPressedProperty();

protected:
	virtual void onClick();
	virtual void onKeyDown();
	virtual void onKeyUp();
	virtual void onMouseEnter();
	virtual void onMouseMove();
	virtual void onMouseLeave();
	virtual void onLeftButtonDown();
	virtual void onLeftButtonUp();

};

}
}