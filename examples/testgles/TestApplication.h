#pragma once
#include "TestBase.h"
#include "gles/Application.h"
#include "system/Window.h"
#include "system/WindowEvent.h"
#include "gles/Painter.h"
#include "gles/Context.h"

class MyApplication : public nb::gl::Gles::Application, public nb::System::WindowEvent
{
public:
	MyApplication();
	~MyApplication();

	void DrawTriangles();
	void DrawQuadrangles();
	void DrawEllipses();
	void DrawCubes();

protected:
	virtual void InitializeOverride();
	virtual void PreRenderOverride();
	virtual void OnIdledOverride();

private:
	virtual void OnPrimaryAction(PrimaryAction action);
	virtual void OnResize(int width, int height);
	virtual void OnPointerAction(PointerAction action, int x, int y);
	virtual void OnKeyAction(KeyAction action, KeyCode key, int mask);

	nb::gl::egl::Context		*m_Context;
	nb::gl::Gles::Painter		m_Painter;
	std::vector<nb::gl::Gles::RenderObject *>	m_RenderObjects;
};

class TestApplication : public TestBase
{
public:
	virtual void Test();

private:
};
