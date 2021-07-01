#pragma once
#include "imgui.h"
#include "rttr/type.h"

struct GLFWwindow;

namespace nb
{
	
class ImGuiView
{
public:
	ImGuiView(GLFWwindow *window);
	virtual ~ImGuiView() = default;

	virtual void onInit() {}
	virtual void onRender() {}

	GLFWwindow *getWindow() const { return m_window; }

private:
	void beginFrame();
	void endFrame();

	GLFWwindow *m_window;
	friend class ImGuiHelper;
};

class ImGuiHelper
{
public:
	static void render(ImGuiView *view);
	static int run(ImGuiView *view);
	static void enableRender(bool enable);
	static bool isEnableRender();
};

class ImGuiWidget
{
public:
	static void showPropertyEditor(rttr::instance &obj);
};

}