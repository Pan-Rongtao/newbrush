#include "gui/Canvas.h"

using namespace nb::core;
using namespace nb::gui;

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::setTop(std::shared_ptr<UIElement> element, double fTopLength)
{
	std::vector<std::shared_ptr<UIElement>> children = Children;
}

double Canvas::getTop(std::shared_ptr<UIElement> element)
{
	std::vector<std::shared_ptr<UIElement>> children = Children;
	return 0.0;
}

void Canvas::setBottom(std::shared_ptr<UIElement> element, double fBottomLength)
{
}


double Canvas::getBottom(std::shared_ptr<UIElement> element)
{
	std::vector<std::shared_ptr<UIElement>> children = Children;
	return 0.0;
}

void Canvas::setLeft(std::shared_ptr<UIElement> element, double fLeftLength)
{
}


double Canvas::getLeft(std::shared_ptr<UIElement> element)
{
	std::vector<std::shared_ptr<UIElement>> children = Children;
	return 0.0;
}

void Canvas::setRight(std::shared_ptr<UIElement> element, double fRightLength)
{
}

double Canvas::getRight(std::shared_ptr<UIElement> element)
{
	std::vector<std::shared_ptr<UIElement>> children = Children;
	return 0.0;
}

Size Canvas::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Canvas::arrangeOverride(const Size & finalSize)
{
	return Size();
}