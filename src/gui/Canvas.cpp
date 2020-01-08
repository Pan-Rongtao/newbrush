#include "gui/Canvas.h"
#include "core/DependencyProperty.h"

using namespace nb;
using namespace nb::gui;

Canvas::Canvas()
{
}

void Canvas::setLeft(std::shared_ptr<UIElement> element, float left)
{
	if (m_children.contains(element))
		DependencyProperty::registerAttached(element, AttachedPropertyLeft, left);
}

float Canvas::getLeft(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyLeft);
	return v.isEmpty() ? NAN : v.convert<float>();
}

void Canvas::setRight(std::shared_ptr<UIElement> element, float right)
{
	if (m_children.contains(element))
		DependencyProperty::registerAttached(element, AttachedPropertyRight, right);
}

float Canvas::getRight(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyRight);
	return v.isEmpty() ? NAN : v.convert<float>();
}

void Canvas::setTop(std::shared_ptr<UIElement> element, float top)
{
	if (m_children.contains(element))
		DependencyProperty::registerAttached(element, AttachedPropertyTop, top);
}

float Canvas::getTop(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyTop);
	return v.isEmpty() ? NAN : v.convert<float>();
}

void Canvas::setBottom(std::shared_ptr<UIElement> element, float bottom)
{
	if (m_children.contains(element))
		DependencyProperty::registerAttached(element, AttachedPropertyBottom, bottom);
}

float Canvas::getBottom(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyBottom);
	return v.isEmpty() ? NAN : v.convert<float>();
}

//位设置宽高则默认为0
Size Canvas::measureOverride(const Size & availableSize)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto w = child->get<float>(WidthProperty());
		auto h = child->get<float>(HeightProperty());
		child->measure(Size((std::isnan(w) ? 0.0f : w), (std::isnan(h) ? 0.0f : h)));
	}
	return availableSize;
}

Size Canvas::arrangeOverride(const Size & finalSize)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto x = getLeft(child);
		auto y = getTop(child);
		if (std::isnan(x))	x = 0.0;
		if (std::isnan(y))	y = 0.0;
		auto desiredSize = child->get<Size>(DesiredSizeProperty());
				
		child->arrage(Rect(x, y, desiredSize.width(), desiredSize.height()));
	}
	return finalSize;
}