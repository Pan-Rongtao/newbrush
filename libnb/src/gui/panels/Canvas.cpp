#include "newbrush/gui/panels/Canvas.h"

using namespace nb;

DependencyPropertyPtr Canvas::LeftProperty()
{
	static auto dp = DependencyProperty::registerAttached<Canvas, float>("Left", NAN, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Canvas::RightProperty()
{
	static auto dp = DependencyProperty::registerAttached<Canvas, float>("Right", NAN, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Canvas::TopProperty()
{
	static auto dp = DependencyProperty::registerAttached<Canvas, float>("Top", NAN, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Canvas::BottomProperty()
{
	static auto dp = DependencyProperty::registerAttached<Canvas, float>("Bottom", NAN, nullptr, nullptr, nullptr);
	return dp;
}

void Canvas::setLeft(UIElementPtr element, float left)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(LeftProperty(), left);
}

float Canvas::getLeft(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue<float>(LeftProperty());
}

void Canvas::setRight(UIElementPtr element, float right)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(RightProperty(), right);
}

float Canvas::getRight(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue<float>(RightProperty());
}

void Canvas::setTop(UIElementPtr element, float top)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(TopProperty(), top);
}

float Canvas::getTop(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue<float>(TopProperty());
}

void Canvas::setBottom(UIElementPtr element, float bottom)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(BottomProperty(), bottom);
}

float Canvas::getBottom(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue<float>(BottomProperty());
}

//未设置宽高则默认为0
Size Canvas::measureOverride(const Size & availableSize)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto w = child->getValue<float>(WidthProperty());
		auto h = child->getValue<float>(HeightProperty());
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
		auto desiredSize = child->desiredSize();
				
		child->arrage(Rect(x, y, desiredSize.width(), desiredSize.height()));
	}
	return finalSize;
}
