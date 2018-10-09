#include "gles/Display.h"
#include "core/Def.h"
#include <EGL/egl.h>
#if NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <wayland-client.h>
#endif
#include "core/Exception.h"

using namespace nb::gl;
using namespace nb::core;

Display::Display()
: m_Handle(nullptr)
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

bool Display::isNull() const
{
	return m_Handle == nullptr;
}

long Display::id() const
{
	return m_Id;
}

void *Display::handle() const
{
	return m_Handle;
}

Display Display::defaultx()
{
	EGLNativeDisplayType id = EGLNativeDisplayType(-1);
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11
	id = EGL_DEFAULT_DISPLAY;
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	id = (EGLNativeDisplayType)(wl_display_connect(nullptr));	//如果使用wayland，传入EGL_DEFAULT_DISPLAY会导致eglInitialize挂死
#else
#error "not realize fun Display::Default() in this platform.\r\n"
#endif

	return Display((long)id);
}
