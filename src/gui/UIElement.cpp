#include "gui/UIElement.h"

using namespace nb::core;
using namespace nb::gui;

UIElement::UIElement()
{
	Visibility.setNotify(std::bind(&UIElement::onVisibilityChanged, this, std::placeholders::_1, std::placeholders::_2));
	Opacity.setNotify(std::bind(&UIElement::onOpacityChanged, this, std::placeholders::_1, std::placeholders::_2));
	Focusable.setNotify(std::bind(&UIElement::onFocusableChanged, this, std::placeholders::_1, std::placeholders::_2));
	DesiredSize.setNotify(std::bind(&UIElement::onDesiredSizeChanged, this, std::placeholders::_1, std::placeholders::_2));
	Magin.setNotify(std::bind(&UIElement::onMaginChanged, this, std::placeholders::_1, std::placeholders::_2));
}

UIElement::~UIElement()
{
}

void UIElement::measure(const Size & availabelSize)
{
}

void UIElement::arrage(const Rect & finalRect)
{
}

Size UIElement::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size UIElement::arrangeOverride(const Size & finalSize) const
{
	return finalSize;
}

void UIElement::onVisibilityChanged(const bool & _old, const bool & _new)
{
}

void UIElement::onOpacityChanged(const double & _old, const double & _new)
{
}

void UIElement::onFocusableChanged(const bool & _old, const bool & _new)
{
}

void UIElement::onDesiredSizeChanged(const Size & _old, const Size & _new)
{
}

void UIElement::onMaginChanged(const Thickness & _old, const Thickness & _new)
{
}
