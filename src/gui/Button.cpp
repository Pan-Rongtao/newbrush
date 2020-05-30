#include "newbrush/gui/Button.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

Button::Button()
{
}

DependencyProperty Button::IsCancelProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsCancel", false, nullptr, nullptr, nullptr, PropertyCategory::Public(), "是否是取消按钮，用户可用Esc来调用默认按钮", 2);
	return dp;
}

DependencyProperty Button::IsDefaultProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsDefault", false, nullptr, nullptr, nullptr, PropertyCategory::Public(), "是否是默认按钮，用户可用Enter来调用默认按钮", 3);
	return dp;
}

std::shared_ptr<MetaObject> Button::getMetaObject()
{
	auto meta = MetaObject::get<Button, ButtonBase>("内容控件", "Button", "按钮。可进行点击交互的控件。", [] {return std::make_shared<Button>(); });
	meta->addProperty(IsCancelProperty(), "公共", "是否是取消按钮，用户可用Esc来调用默认按钮", PropertyDescriptor::Boolean);
	meta->addProperty(IsDefaultProperty(), "公共", "是否是默认按钮，用户可用Enter来调用默认按钮", PropertyDescriptor::Boolean);
	return meta;
}

