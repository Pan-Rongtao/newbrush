#include "gui/Button.h"
#include "gui/DependencyProperty.h"

using namespace nb::gui;
using namespace nb::core;
using namespace nb::gui;

Button::Button()
	: m_pressed(false)
{ 
}

Button::~Button()
{

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
