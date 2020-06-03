#include "newbrush/gui/Button.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Button::Button()
{
}

DependencyPropertyPtr Button::IsCancelProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsCancel", false, nullptr, nullptr, nullptr, PropertyCategory::Public(), "是否是取消按钮，用户可用Esc来调用默认按钮", 2);
	return dp;
}

DependencyPropertyPtr Button::IsDefaultProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsDefault", false, nullptr, nullptr, nullptr, PropertyCategory::Public(), "是否是默认按钮，用户可用Enter来调用默认按钮", 3);
	return dp;
}
