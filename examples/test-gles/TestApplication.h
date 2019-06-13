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

	void DrawTriangles();
	void DrawQuadrangles();
	void DrawEllipses();
	void DrawCubes();
	void DrawSphere();
	void drawPhone();
	void drawModel();
	void drawGlyph();

protected:
	virtual void preRender() override;

private:
	void OnResize(const nb::core::Window::ResizeArgs &args);
	void OnPointerAction(const nb::core::Window::PointerEventArgs &args);
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
