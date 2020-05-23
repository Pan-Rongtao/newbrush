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

UIElement * VisualTreeHelper::findChild(UIElement * element, const std::string & name)
{
	if (element == nullptr)
	{
		nbThrowException(std::invalid_argument, "element is nullptr.");
	}

	for (int i = 0; i < getChildrenCount(element); ++i)
	{
		auto child = getChild(element, i);
		auto childName = child->getValue<std::string>(UIElement::NameProperty());
		if (childName == name)
		{
			return child;
		}
	}

	return nullptr;
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

UIElement * VisualTreeHelper::lookupNode(UIElement * node, const std::string & path)
{
	auto nodeNames = nb::stringSplit(path, ".", false);
	auto p = node;
	for (int i = 0; i < nodeNames.size(); ++i)
	{
		if (!p)	break;

		auto curNodeName = p->getValue<std::string>(UIElement::NameProperty());
		if (curNodeName == nodeNames[i])
		{
			if (i == nodeNames.size() - 1)
			{
				return p;
			}
			else
			{
				p = findChild(node, nodeNames[i + 1]);
			}
		}
		else
		{
			break;
		}
	}

	return nullptr;
}
