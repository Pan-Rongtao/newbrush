#pragma once
#include "../TestBase.h"
#include "gles/Application.h"
#include "core/Window.h"
#include "gles/Context.h"
#include "core/Timer.h"
#include "gles/Camera.h"
#include "gles/Surface.h"
#include "gles/Window.h"

class MyApplication : public nb::gl::Application
{
public:
	MyApplication();
	~MyApplication();

	void DrawTriangles(bool bOrigin);
	void DrawQuadrangles(bool bOrigin);
	void DrawEllipses(bool bOrigin);
	void DrawCubes(bool bOrigin);
	void DrawSphere(bool bOrigin);
	void drawPhone(bool bOrigin);
	void drawModel(bool bOrigin);

protected:
	virtual void InitializeOverride();
	virtual void PreRenderOverride();
	virtual void OnIdledOverride();

private:
	void OnResize(const nb::core::Window::ResizeArgs &args);
	void OnPointerAction(const nb::core::Window::PointerEventArgs &args);
	void OnKeyAction(const nb::core::Window::KeyEventArgs &args);

	void OnTick(const nb::core::Timer::TickArgs & param);

	std::shared_ptr<nb::gl::Context>					m_context;
	std::shared_ptr<nb::gl::Surface>					m_surface;
	std::shared_ptr<nb::gl::Window>						m_window;
	nb::core::Timer									m_timer;
};

class TestApplication : public TestBase
{
public:
	virtual void test();

private:
};
