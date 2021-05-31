#include "newbrush/Helper.h"

using namespace nb;

Node2D * TreeHelper::getRoot(Node2D * node)
{
	auto *root = node;
	while (root->getParent())
	{
		root = root->getParent();
	}
	return (Node2D *)root;
}

Point TreeHelper::getWolrdOffset(Node2D *node)
{
	Point pt;
	auto p = node;
	do {
		auto offset = p->getOffsetToParent();
		pt += offset;
	} while ((p->getParent()) && (p = (Node2D *)p->getParent()));
	return pt;
}

std::vector<ref<Node2D>> TreeHelper::getAllChildren(ref<Node2D> node)
{
	std::function<void(ref<Node2D> node, std::vector<ref<Node2D>> &nodes)> loop = [&loop](ref<Node2D> node, std::vector<ref<Node2D>> &nodes)
	{
		for (auto child : node->children())
		{
			nodes.push_back(child);
			if (!child->children().empty())
				loop(child, nodes);
		}
	};
	std::vector<ref<Node2D>> ret{ node };
	loop(node, ret);
	return ret;
}

void TreeHelper::touchThunk(ref<Node2D> node, const TouchEventArgs &e)
{
	if (node)
	{
		auto nodes = TreeHelper::getAllChildren(node);
		for (auto node : nodes)
		{
			node->touchThunk(e);
		}
	}

}

void TreeHelper::scrollThunk(ref<Node2D> node, const ScrollEventArgs & e)
{
	if (node)
	{
		auto nodes = TreeHelper::getAllChildren(node);
		for (auto node : nodes)
		{
			node->scrollThunk(e);
		}
	}
}

void TreeHelper::keyThunk(ref<Node2D> node, const KeyEventArgs & e)
{
	if (node)
	{
		auto nodes = TreeHelper::getAllChildren(node);
		for (auto node : nodes)
		{
			node->keyThunk(e);
		}
	}
}
