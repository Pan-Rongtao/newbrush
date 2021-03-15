#include "newbrush/UserControl.h"
#include "newbrush/Renderer2D.h"

using namespace nb;

Button::Button()
	: m_checked(false)
{
}

void Button::setBkgndNormal(ref<Brush> brush)
{
	m_bkgndNormal = brush;
}

void Button::setBkgndPress(ref<Brush> brush)
{
	m_bkgndPress = brush;
}

void Button::setBkgndDisable(ref<Brush> brush)
{
	m_bkgndDisable = brush;
}

void Button::setBkgndCheck(ref<Brush> brush)
{
	m_bkgndCheck = brush;
}

void Button::setBkgndFocus(ref<Brush> brush)
{
	m_bkgndFocus = brush;
}

void Button::setCheck(bool check)
{
	m_checked = check;
}

bool Button::isChecked() const
{
	return m_checked;
}

void Button::onTouch(const TouchEventArgs & e)
{
	ButtonBase::onTouch(e);
}

void Button::onFocusChanged(const FocusEventArgs & e)
{
}

void Button::onRender()
{
	Rect rc = getRenderRect();
	ref<Brush> brush;
	if (isEnable())
	{
		if (isChecked())
		{
			brush = m_bkgndCheck;
		}
		else if (isPressed())
		{
			brush = m_bkgndPress;
		}
		else if (hasFocus())
		{
			brush = m_bkgndFocus;
		}
		else
		{
			brush = m_bkgndNormal;
		}
	}
	else
	{
		brush = m_bkgndDisable;
	}

	if (!brush)
	{
		brush = m_bkgndNormal;
	}

	drawBrush(brush);
}
