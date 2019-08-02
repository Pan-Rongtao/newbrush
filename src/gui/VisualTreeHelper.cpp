#include "gui/VisualTreeHelper.h"
#include "gui/Panel.h"
#include "gui/UIElement.h"
#include "gui/ContentControl.h"

using namespace nb::gui;

uint32_t VisualTreeHelper::getChildCount(UIElement *element)
{
	if (dynamic_cast<Panel *>(element) != nullptr)
	{
		return ((Panel *)element)->Children().size();
	}
	else if(dynamic_cast<ContentControl *>(element) != nullptr)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

UIElement *VisualTreeHelper::getChild(UIElement *element, uint32_t childIndex)
{
	if (dynamic_cast<Panel *>(element) != nullptr)
	{
		auto p = (Panel *)(element);
		return childIndex >= p->Children().size() ? nullptr : p->Children()[childIndex].get();
	}
	else if (dynamic_cast<ContentControl *>(element) != nullptr)
	{
		return ((ContentControl*)(element))->Content().get();
	}
	else
	{
		return nullptr;
	}
}
