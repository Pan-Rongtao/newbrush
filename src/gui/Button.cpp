#include "newbrush/gui/Button.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

Button::Button()
{
}

DependencyProperty Button::IsCancelProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsCancel", false);
	return dp;
}

DependencyProperty Button::IsDefaultProperty()
{
	static auto dp = DependencyProperty::registerDependency<Button, bool>("IsDefault", false);
	return dp;
}

std::shared_ptr<MetaObject> Button::getMetaObject()
{
	auto meta = MetaObject::get<Button, ButtonBase>("内容控件", "Button", "按钮。可进行点击交互的控件。", [] {return std::make_shared<Button>(); });
	return meta;
}

