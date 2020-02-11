#pragma once
#include "newbrush/gui/ContentControl.h"

namespace nb{ 
namespace gui{

enum class ClickModeE
{
	hover,	//鼠标悬停在控件上时引发click事件
	press,	//压下时引发click事件
	release,//压下和释放按钮时引发click事件
};

class NB_API ButtonBase : public ContentControl
{
public:
	ButtonBase();
	virtual ~ButtonBase() = default;

	static DependencyProperty	ClickModeProperty();	//点击模式的依赖属性
	static DependencyProperty	IsPressedProperty();	//是否压下的依赖属性

	struct ClickArgs {};
	Event<ClickArgs>				Click;					//点击事件

															
protected:
	virtual bool isEnableCore();							//重载以返回子类的可用状态

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