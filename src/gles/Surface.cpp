#include <EGL/egl.h>
#include <stdlib.h>
#include "gles/Surface.h"
#include "gles/Egl.h"
#include "EglMaster.h"

using namespace nb::gl;

Surface::Surface()
	: m_handle(nullptr)
{
}

Surface::~Surface()
{
	eglDestroySurface(nb::gl::getDisplay()->handle(), m_handle);
}

void Surface::setWidth(int width)
{
	eglSurfaceAttrib(nb::gl::getDisplay()->handle(), m_handle, EGL_WIDTH, width);
}

void Surface::setHeight(int height)
{
	eglSurfaceAttrib(nb::gl::getDisplay()->handle(), m_handle, EGL_HEIGHT, height);
}

int Surface::width() const
{
	if (!nb::gl::getDisplay())
		nbThrowException(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	const char *p = eglQueryString(nb::gl::getDisplay()->handle(), EGL_WIDTH);
	return atoi(p);
}

int Surface::height() const
{
	if (!nb::gl::getDisplay())
		nbThrowException(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	const char *p = eglQueryString(nb::gl::getDisplay()->handle(), EGL_HEIGHT);
	return atoi(p);
}

void *Surface::handle() const
{
	return m_handle;
}

///////////////////////////////////
WindowSurface::WindowSurface(int width, int height, long windowHandle)
	: m_windowHandle(windowHandle)
{
	if (!getDisplay())
		nbThrowException(std::logic_error, "gl init needed, use nb::gl::initialize to init.");
	else if (!getConfigure())
		nbThrowException(std::logic_error, "gl configure needed, use nb::gl::setConfigure to set configure.");

	m_handle = eglCreateWindowSurface(nb::gl::getDisplay()->handle(), nb::gl::getConfigure()->handle(), (EGLNativeWindowType)windowHandle, nullptr);
	if (!eglQuerySurface(nb::gl::getDisplay()->handle(), m_handle, EGL_WIDTH, &width)
		|| !eglQuerySurface(nb::gl::getDisplay()->handle(), m_handle, EGL_HEIGHT, &height))
		nbThrowException(std::runtime_error, "eglQuerySurface fail, eglGetError[%d]", eglGetError());

	EglMaster::windowSurfaces().push_back(this);
}

WindowSurface::~WindowSurface()
{
	auto &wses = EglMaster::windowSurfaces();
	auto iter = std::find(wses.begin(), wses.end(), this);
	if (iter != wses.end())
		wses.erase(iter);
}

long WindowSurface::windowHandle()
{
	return m_windowHandle;
}

///////////////////////
PbufferSurface::PbufferSurface(int width, int height)
{
}

///////////////////////
PixmapSurface::PixmapSurface(int width, int height, void *pixmapHandle)
	: m_pixmapHandle(pixmapHandle)
{
}

void *PixmapSurface::pixmapHandle()
{
	return m_pixmapHandle;
}

const void *PixmapSurface::pixmapHandle() const
{
	return m_pixmapHandle;
}