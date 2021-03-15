#include "newbrush/Helper.h"

using namespace nb;

Node2D * TreeHelper::getRoot(Node2D * node)
{
	Node *root = node;
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
		nodes.push_back(node);
		for (auto child : node->children())
		{
			if (!child->children().empty())
				loop(nb::as<Node2D>(child), nodes);
		}
	};
	std::vector<ref<Node2D>> ret;
	loop(node, ret);
	return ret;
}

ref<Node> TreeHelper::find(ref<Node> node, const std::string & name)
{
	std::function<void(ref<Node> node, const std::string &name, ref<Node> &ret)> loopFind = [&loopFind](ref<Node> node, const std::string &name, ref<Node> &ret)
	{
		if (!node) return;
		if (ret) return;

		if (node && node->getName() == name)
		{
			ret = node;
		}

		//未找到就才需要再继续了
		if (ret == nullptr)
		{
			for (auto child : node->children())
			{
				loopFind(child, name, ret);
			}
		}
	};

	ref<Node> ret;
	loopFind(node, name, ret);
	return ret;
}
