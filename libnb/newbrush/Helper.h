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

	static glm::vec4 getBox(const std::vector<glm::vec2> &points);
};

class NB_API SystemHelper
{
public:
	static std::string getSystemInfos();
	static void printSystemInfos();

	static void updateFPS();
	static float getFPS();

	static void enableFPSInfo(bool enable);
};

class RttrRegistration
{
public:
	//执行注册
	static void doRegister();

private:
	static void registerEnums();
	static void registerTypes();
	static void registerConverters();
};

}