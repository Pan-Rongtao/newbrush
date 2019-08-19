#include "gui/Button.h"
#include "gui/DependencyProperty.h"

using namespace nb::gui;
using namespace nb::core;
using namespace nb::gui;

Button::Button()
	: m_pressed(false)
{
	IsCancel.notify([&](const float &_old, const float &_new) { setValue<float>(IsCancelProperty(), _new); });
	IsDefault.notify([&](const float &_old, const float &_new) { setValue<float>(IsDefaultProperty(), _new); });
}

const DependencyProperty Button::IsCancelProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Button, bool>("IsCancel", false);
	return dp;
}

const DependencyProperty Button::IsDefaultProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Button, bool>("IsDefault", false);
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
	m_pressed = true;
}

void Button::onMouseLeftButtonUp()
{
	if (m_pressed)
		Click.dispatch({});
}
