#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/core/base/Point.h"

namespace nb{

class UIElement;
class NB_API VisualTreeHelper
{
public:
	//获取子节点个数
	static uint32_t getChildrenCount(UIElement *element);

	//获取下标子节点
	static UIElement * getChild(UIElement *element, uint32_t childIndex);

	static UIElement *findChild(UIElement *element, const std::string &name);

	//获取父节点
	static UIElement * getParent(UIElement *element);

	//命中测试
	static bool hitTest(UIElement *element, const Point &point);

	static UIElement *findLogicalNode(UIElement *logicalTreeNode, const std::string &name);

	static UIElement *lookupNode(UIElement *node, const std::string &path);

	static Point getPosition(UIElement *relativeTo);
};

}