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

using namespace nb::media;
using namespace nb::gl;

class MyApplication : public nb::gl::Application
{
public:
	MyApplication();

	void drawLines();
	void drawPolylines();
	void drawTriangles();
	void drawQuadrangles();
	void drawEllipses();
	void drawCubes();
	void drawSphere();
	void drawPhone();
	void drawModel();
	void drawGlyph();
	void drawGlyphBunch();

	bool isHit(std::shared_ptr<RenderObject> obj, int x, int y) const;
	void hitTest(int x, int y);

protected:
	virtual void preRender() override;

private:
	void onResize(const nb::core::Window::ResizeArgs &args);
	void onMouseEnter(const nb::core::Window::MouseEnterEventArgs &args);
	void onMouseLeave(const nb::core::Window::MouseLeaveEventArgs &args);
	void onMouseMove(const nb::core::Window::MouseMoveEventArgs &args);
	void onMouseLeftButton(const nb::core::Window::MouseLeftButtonEventArgs &args);
	void onMouseRightButton(const nb::core::Window::MouseRightButtonEventArgs &args);
	void onMouseMiddleButton(const nb::core::Window::MouseMiddleButtonEventArgs &args);
	void onMouseWheel(const nb::core::Window::MouseWheelEventArgs &args);
	void onKeyAction(const nb::core::Window::KeyEventArgs &args);

	void OnTick(const nb::core::Timer::TickArgs & param);

	std::shared_ptr<nb::gl::Context>					m_context;
	std::shared_ptr<nb::gl::Surface>					m_surface;
	std::shared_ptr<nb::gl::Window>						m_window;
	nb::core::Timer										m_timer;
};

class TestApplication : public TestBase
{
public:
	virtual void test();

private:
};
