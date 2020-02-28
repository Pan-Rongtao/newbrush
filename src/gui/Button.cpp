#include "newbrush/gui/Button.h"

using namespace nb;
using namespace nb::gui;

Button::Button()
	: m_pressed(false)
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

void Button::onMouseDown()
{
}

void Button::onMouseUp()
{
}

void Button::onMouseLeftButtonDown()
{

}

void Button::onMouseLeftButtonUp()
{
}
