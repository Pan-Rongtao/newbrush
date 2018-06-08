#include "Display_Internal.h"
#include <EGL/egl.h>
#include "system/PlatformConfigure.h"
#include "core/Exception.h"

using nb::EGL::Display_Internal;
using nb::Core::Exception;

Display_Internal::Display_Internal(EGLNativeDisplayType id)
{
	m_Handle = eglGetDisplay(id);
	if(m_Handle == EGL_NO_DISPLAY || eglGetError() != EGL_SUCCESS)
		NB_THROW_EXCEPTION("error display with id.");

	int major = 0;
	int minor = 0;
	EGLBoolean b = eglInitialize(m_Handle, &major, &minor);
	if(b == false)
		NB_THROW_EXCEPTION("display init fail.");
}

EGLNativeDisplayType Display_Internal::GetId() const
{
	return m_Id;
}

EGLDisplay Display_Internal::GetHandle() const
{
	return m_Handle;
}

Display_Internal Display_Internal::Default()
{
	EGLNativeDisplayType id = EGLNativeDisplayType(-1);
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11
	id = EGL_DEFAULT_DISPLAY;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	id = EGL_DEFAULT_DISPLAY;
#else
#error "not realize fun Display_Internal::Default() in this platform.\r\n"
#endif

	return Display_Internal(id);
}
