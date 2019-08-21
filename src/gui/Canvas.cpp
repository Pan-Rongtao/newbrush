#include "gui/Canvas.h"
#include "gui/DependencyProperty.h"

using namespace nb;
using namespace nb::gui;

Canvas::Canvas()
{
}

void Canvas::setLeft(std::shared_ptr<UIElement> element, float left)
{
	if (containsChild(element))
		DependencyProperty::registerAttached(element, AttachedPropertyLeft, left);
}

float Canvas::getLeft(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyLeft);
	return v.empty() ? NAN : any_cast<float>(v);
}

void Canvas::setRight(std::shared_ptr<UIElement> element, float right)
{
	if (containsChild(element))
		DependencyProperty::registerAttached(element, AttachedPropertyRight, right);
}

float Canvas::getRight(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyRight);
	return v.empty() ? NAN : any_cast<float>(v);
}

void Canvas::setTop(std::shared_ptr<UIElement> element, float top)
{
	if (containsChild(element))
		DependencyProperty::registerAttached(element, AttachedPropertyTop, top);
}

float Canvas::getTop(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyTop);
	return v.empty() ? NAN : any_cast<float>(v);
}

void Canvas::setBottom(std::shared_ptr<UIElement> element, float bottom)
{
	if (containsChild(element))
		DependencyProperty::registerAttached(element, AttachedPropertyBottom, bottom);
}

float Canvas::getBottom(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyBottom);
	return v.empty() ? NAN : any_cast<float>(v);
}

//位设置宽高则默认为0
Size Canvas::measureOverride(const Size & availableSize)
{
	for (auto child : m_children)
	{
		child->measure(Size((std::isnan(child->Width()) ? 0.0f : child->Width()), (std::isnan(child->Height()) ? 0.0f : child->Height())));
	}
	return availableSize;
}

Size Canvas::arrangeOverride(const Size & finalSize)
{
	for (auto child : m_children)
	{
		auto x = getLeft(child);
		auto y = getTop(child);
		if (std::isnan(x))	x = 0.0;
		if (std::isnan(y))	y = 0.0;
		auto w = child->DesiredSize().width();
		auto h = child->DesiredSize().height();
				
		child->arrage(Rect(x, y, w, h));
	}
	return finalSize;
}