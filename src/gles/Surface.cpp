#include <EGL/egl.h>
#include <stdlib.h>
#include "gles/Surface.h"
#include "gles/Egl.h"
#include "core/Exception.h"
#include "EglMaster.h"

using namespace nb::core;
using namespace nb::gl;

Surface::Surface()
{
}

Surface::~Surface()
{
	eglDestroySurface(nb::gl::getCurrentDisplay().handle(), m_Handle);
}

void Surface::setWidth(int width)
{
	eglSurfaceAttrib(nb::gl::getCurrentDisplay().handle(), m_Handle, EGL_WIDTH, width);
//	eglQuerySurface(nb::gl::egl::getCurrentDisplay().handle(), m_Handle, EGL_WIDTH, &width);
}

void Surface::setHeight(int height)
{
	eglSurfaceAttrib(nb::gl::getCurrentDisplay().handle(), m_Handle, EGL_HEIGHT, height);
//	eglQuerySurface(nb::gl::egl::getCurrentDisplay().handle(), m_Handle, EGL_HEIGHT, &height);
}

int Surface::width() const
{
	if(nb::gl::getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	const char *p = eglQueryString(nb::gl::getCurrentDisplay().handle(), EGL_WIDTH);
	return atoi(p);
}

int Surface::height() const
{
	if(nb::gl::getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	const char *p = eglQueryString(nb::gl::getCurrentDisplay().handle(), EGL_HEIGHT);
	return atoi(p);
}

void *Surface::handle() const
{
	return m_Handle;
}

///////////////////////////////////
WindowSurface::WindowSurface(int width, int height, long windowHandle)
: m_WindowHandle(windowHandle)
{
	if(nb::gl::getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");
	if(nb::gl::getCurrentConfigure().isNull())
		NB_THROW_EXCEPTION("none configure set, use egl::setconfigure to set one configure.");

	m_Handle = eglCreateWindowSurface(nb::gl::getCurrentDisplay().handle(), nb::gl::getCurrentConfigure().handle(), (EGLNativeWindowType)windowHandle, nullptr);
	eglQuerySurface(nb::gl::getCurrentDisplay().handle(), m_Handle, EGL_WIDTH, &width);
	eglQuerySurface(nb::gl::getCurrentDisplay().handle(), m_Handle, EGL_HEIGHT, &height);

	nb::gl::SurfacesMaster::push(this);
}

WindowSurface::~WindowSurface()
{
	nb::gl::SurfacesMaster::erease(this);
}

long WindowSurface::windowHandle()
{
	return m_WindowHandle;
}

///////////////////////
PbufferSurface::PbufferSurface(int width, int height)
{
}

///////////////////////
PixmapSurface::PixmapSurface(int width, int height, void *pixmapHandle)
: m_PixmapHandle(pixmapHandle)
{
}

void *PixmapSurface::pixmapHandle()
{
	return m_PixmapHandle;
}

const void *PixmapSurface::pixmapHandle() const
{
	return m_PixmapHandle;
}