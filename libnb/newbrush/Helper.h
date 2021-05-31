#pragma once
#include "newbrush/Node2D.h"

namespace nb
{

class NB_API TreeHelper
{
public:
	static Node2D *getRoot(Node2D *node);

	static Point getWolrdOffset(Node2D *node);

	static std::vector<ref<Node2D>> getAllChildren(ref<Node2D> node);

	static void touchThunk(ref<Node2D> node, const TouchEventArgs &e);
	static void scrollThunk(ref<Node2D> node, const ScrollEventArgs &e);
	static void keyThunk(ref<Node2D> node, const KeyEventArgs &e);
};

}