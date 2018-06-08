#include <EGL/egl.h>
#include <stdlib.h>
#include "gles/Surface.h"
#include "gles/Egl.h"
#include "core/Exception.h"
#include "EglMaster.h"

using nb::Core::Exception;
using nb::gl::egl::Surface;
using nb::gl::egl::WindowSurface;
using nb::gl::egl::PbufferSurface;
using nb::gl::egl::PixmapSurface;

Surface::Surface()
{
}

Surface::~Surface()
{
	eglDestroySurface(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), m_Handle);
}

int Surface::GetWidth() const
{
	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	const char *p = eglQueryString(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), EGL_WIDTH);
	return atoi(p);
}

int Surface::GetHeight() const
{
	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	const char *p = eglQueryString(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), EGL_HEIGHT);
	return atoi(p);
}

void *Surface::GetEGLHandle() const
{
	return m_Handle;
}

///////////////////////////////////
WindowSurface::WindowSurface(int width, int height, long windowHandle)
: m_WindowHandle(windowHandle)
{
	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");
	if(nb::gl::egl::GetCurrentConfigure().IsNull())
		NB_THROW_EXCEPTION("none configure set, use egl::setconfigure to set one configure.");

	m_Handle = eglCreateWindowSurface(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), nb::gl::egl::GetCurrentConfigure().GetEGLHandle(), (EGLNativeWindowType)windowHandle, NULL);
	eglQuerySurface(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), m_Handle, EGL_WIDTH, &width);
	eglQuerySurface(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), m_Handle, EGL_HEIGHT, &height);

	nb::gl::egl::SurfacesMaster::Push(this);
}

WindowSurface::~WindowSurface()
{
	nb::gl::egl::SurfacesMaster::Erease(this);
}

long WindowSurface::GetWindowHandle()
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

void *PixmapSurface::GetPixmapHandle()
{
	return m_PixmapHandle;
}
