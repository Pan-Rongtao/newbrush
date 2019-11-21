#pragma once
#include "../TestBase.h"
#include "core/Window.h"
#include "core/Timer.h"
#include "media/Font.h"
#include "gles/Application.h"
#include "gles/Context.h"
#include "gles/Camera.h"
#include "gles/Surface.h"
#include "gles/Window.h"
#include "gles/Display.h"

using namespace nb;
using namespace nb::gl;

class MyApplication : public nb::gl::Application
{
public:
	MyApplication();

	void drawTriangles();
	void drawQuadrangles();
	void drawCubes();
	void drawSphere();
	void drawPhone();
	void drawModel();
	void drawGlyph();
	void drawGlyphBunch();
	void drawStrip();

	bool isHit(std::shared_ptr<RenderObject> obj, int x, int y) const;
	void hitTest(int x, int y);

protected:
	virtual void preRender() override;

private:
	void onResize(const nb::Window::ResizeArgs &args);
	void onMouseEnter(const nb::Window::MouseEnterEventArgs &args);
	void onMouseLeave(const nb::Window::MouseLeaveEventArgs &args);
	void onMouseMove(const nb::Window::MouseMoveEventArgs &args);
	void onMouseLeftButton(const nb::Window::MouseLeftButtonEventArgs &args);
	void onMouseRightButton(const nb::Window::MouseRightButtonEventArgs &args);
	void onMouseMiddleButton(const nb::Window::MouseMiddleButtonEventArgs &args);
	void onMouseWheel(const nb::Window::MouseWheelEventArgs &args);
	void onKeyAction(const nb::Window::KeyEventArgs &args);

	void OnTick(const Timer::TickArgs & param);

	std::shared_ptr<nb::gl::Context>	m_context;
	std::shared_ptr<nb::gl::Surface>	m_surface;
	std::shared_ptr<nb::gl::Window>		m_window;
	Timer								m_timer;
};

class TestApplication : public TestBase
{
public:
	virtual void test();

private:
};
