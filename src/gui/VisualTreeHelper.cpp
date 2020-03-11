#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/gui/Panel.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/ContentControl.h"
#include "newbrush/gui/Window.h"

using namespace nb;

uint32_t VisualTreeHelper::getChildrenCount(UIElement *element)
{
	return element->childrenCount();
}

UIElement *VisualTreeHelper::getChild(UIElement *element, uint32_t childIndex)
{
	return element->getChild(childIndex);
}

UIElement *VisualTreeHelper::getParent(UIElement * element)
{
	return element->getParent();
}

bool VisualTreeHelper::hitTest(UIElement * element, const Point &point)
{
	return element->hitTestCore(point);
}

UIElement *VisualTreeHelper::findLogicalNode(UIElement * logicalTreeNode, const std::string & name)
{
	if (!logicalTreeNode)
	{
		nbThrowException(std::invalid_argument, "logicalTreeNode is nullptr");
	}
	if (name.empty())
	{
		nbThrowException(std::invalid_argument, "name is empty");
	}

	UIElement* ret = nullptr;
	auto _myName = logicalTreeNode->getValue<std::string>(UIElement::NameProperty());
	if (_myName == name)
	{
		ret = logicalTreeNode;
	}

	if (ret == nullptr)
	{
		for (auto i = 0; i < logicalTreeNode->childrenCount(); ++i)
		{
			auto childNode = logicalTreeNode->getChild(i);
			ret = findLogicalNode(childNode, name);
		}
	}

	return ret;
}
