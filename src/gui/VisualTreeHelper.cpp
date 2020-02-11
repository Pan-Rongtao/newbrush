#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/gui/Panel.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/ContentControl.h"

using namespace nb::gui;

uint32_t VisualTreeHelper::getChildCount(UIElement *element)
{
	return 1;// element->childCount();
}

UIElement *VisualTreeHelper::getChild(UIElement *element, uint32_t childIndex)
{
	return element;// element->childAt(childIndex).get();
}
