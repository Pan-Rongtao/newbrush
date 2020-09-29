#pragma once
#include "newbrush/model/Scene3D.h"
#include "Window.h"

namespace nb 
{

class ConfigScene
{
public:
	void parse(const std::string &path);

	Scene3DPtr getScene() const;
	void loopDraw();

private:
	void onKey(const int &key);
	void onResize(const Size &sz);
	void onCursorPos(const Point &pt);
	void onScroll(const Point &pt);

	Scene3DPtr m_scene;
	WindowPtr m_window;
};

}
