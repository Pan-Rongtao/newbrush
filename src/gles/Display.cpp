#include "gles/Display.h"
#include "system/PlatformConfigure.h"
#include <EGL/egl.h>
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <wayland-client.h>
#endif
#include "core/Exception.h"

using nb::gl::egl::Display;
using nb::Core::Exception;

Display::Display()
: m_Handle(NULL)
, m_Id(-1)
{
}

Display::Display(long id)
{
	m_Handle = eglGetDisplay((EGLNativeDisplayType)id);
	if(m_Handle == EGL_NO_DISPLAY || eglGetError() != EGL_SUCCESS)
		NB_THROW_EXCEPTION("error display with id.");

	int major = 0;
	int minor = 0;
	EGLBoolean b = eglInitialize(m_Handle, &major, &minor);
	if(b == false)
		NB_THROW_EXCEPTION("display init fail.");

	m_Id = id;
}

bool Display::IsNull() const
{
	return m_Handle == NULL;
}

long Display::GetId() const
{
	return m_Id;
}

void *Display::GetEGLHandle() const
{
	return m_Handle;
}

nb::gl::egl::Display nb::gl::egl::Display::Default()
{
	EGLNativeDisplayType id = EGLNativeDisplayType(-1);
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11
	id = EGL_DEFAULT_DISPLAY;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	id = (EGLNativeDisplayType)(wl_display_connect(NULL));	//如果使用wayland，传入EGL_DEFAULT_DISPLAY会导致eglInitialize挂死
#else
#error "not realize fun Display::Default() in this platform.\r\n"
#endif

	return Display((long)id);
}
