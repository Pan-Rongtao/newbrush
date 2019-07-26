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
	void OnResize(const nb::core::Window::ResizeArgs &args);
	void OnMouseAction(const nb::core::Window::MouseEventArgs &args);
	void OnKeyAction(const nb::core::Window::KeyEventArgs &args);

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
