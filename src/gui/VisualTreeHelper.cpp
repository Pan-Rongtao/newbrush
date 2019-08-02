#include "gui/VisualTreeHelper.h"
#include "gui/Panel.h"
#include "gui/UIElement.h"
#include "gui/ContentControl.h"

using namespace nb::gui;

uint32_t VisualTreeHelper::getChildCount(UIElement *element)
{
	return element->childCount();
}

UIElement *VisualTreeHelper::getChild(UIElement *element, uint32_t childIndex)
{
	return element->childAt(childIndex).get();
}
