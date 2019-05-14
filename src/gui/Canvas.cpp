#include "gui/Canvas.h"
#include "gui/AttachedProperty.h"

using namespace nb::core;
using namespace nb::gui;

#define CANVAS_ATTACHED_PROPERTY_LEFT	"Canvas.Left"
#define CANVAS_ATTACHED_PROPERTY_RIGHT	"Canvas.Right"
#define CANVAS_ATTACHED_PROPERTY_TOP	"Canvas.Top"
#define CANVAS_ATTACHED_PROPERTY_BOTTOM	"Canvas.Bottom"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::setLeft(std::shared_ptr<UIElement> element, double left)
{
	if (std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		AttachedProperties::registerAttached(element, CANVAS_ATTACHED_PROPERTY_LEFT, left);
	}
}

double Canvas::getLeft(std::shared_ptr<UIElement> element)
{
	auto v = AttachedProperties::findAttached(element, CANVAS_ATTACHED_PROPERTY_LEFT);
	return v.empty() ? NB_DOUBLE_NAN : any_cast<double>(v);
}

void Canvas::setRight(std::shared_ptr<UIElement> element, double right)
{
	if (std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		AttachedProperties::registerAttached(element, CANVAS_ATTACHED_PROPERTY_RIGHT, right);
	}
}

double Canvas::getRight(std::shared_ptr<UIElement> element)
{
	auto v = AttachedProperties::findAttached(element, CANVAS_ATTACHED_PROPERTY_RIGHT);
	return v.empty() ? NB_DOUBLE_NAN : any_cast<double>(v);
}

void Canvas::setTop(std::shared_ptr<UIElement> element, double top)
{
	if (std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		AttachedProperties::registerAttached(element, CANVAS_ATTACHED_PROPERTY_TOP, top);
	}
}

double Canvas::getTop(std::shared_ptr<UIElement> element)
{
	auto v = AttachedProperties::findAttached(element, CANVAS_ATTACHED_PROPERTY_TOP);
	return v.empty() ? NB_DOUBLE_NAN : any_cast<double>(v);
}

void Canvas::setBottom(std::shared_ptr<UIElement> element, double bottom)
{
	if (std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		AttachedProperties::registerAttached(element, CANVAS_ATTACHED_PROPERTY_BOTTOM, bottom);
	}
}

double Canvas::getBottom(std::shared_ptr<UIElement> element)
{
	auto v = AttachedProperties::findAttached(element, CANVAS_ATTACHED_PROPERTY_BOTTOM);
	return v.empty() ? NB_DOUBLE_NAN : any_cast<double>(v);
}

Size Canvas::measureOverride(const Size & availableSize)
{
	for (auto child : Children())
	{
		child->measure(availableSize);
	}
	return availableSize;
}

Size Canvas::arrangeOverride(const Size & finalSize)
{
	for (auto child : Children())
	{
		Rect rc((float)getLeft(child), (float)getTop(child), child->DesiredSize);
		child->arrage(rc);
	}
	return finalSize;
}