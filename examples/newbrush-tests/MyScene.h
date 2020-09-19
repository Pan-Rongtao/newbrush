#pragma once
#include "newbrush/model/Scene3D.h"
#include "Window.h"

using namespace nb;

class MyScene
{
public:
	MyScene(int width, int height);
	void load(const std::string &path, float scale);

	Scene3DPtr getScene() const;

	void loopDraw();

private:
	void onKey(const int &key);
	void onResize(const Size &sz);
	void onCursorPos(const Point &pt);
	void onScroll(const Point &pt);

	void updateTransform();

	Scene3DPtr m_sc;
	WindowPtr m_window;

	float m_scale;
	float m_angle;
	float m_translate;
};