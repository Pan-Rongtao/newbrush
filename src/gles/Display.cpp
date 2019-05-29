#include "gles/Display.h"
#include "core/Def.h"
#include <EGL/egl.h>
#if NB_OS == NB_OS_LINUX && NB_ARCH == NB_ARCH_ARM
	#include <wayland-client.h>
#endif
#include "core/Exception.h"

using namespace nb::gl;
using namespace nb::core;

Display::Display(long id)
	: m_handle(nullptr)
	, m_id(-1)
{
	m_handle = eglGetDisplay((EGLNativeDisplayType)id);
	int major = 0, minor = 0;
	if(m_handle == EGL_NO_DISPLAY || !eglInitialize(m_handle, &major, &minor))
		NB_THROW_EXCEPTION("error display with id.", eglGetError);

	m_id = id;
}

long Display::id() const
{
	return m_id;
}

void *Display::handle() const
{
	return m_handle;
}

Display Display::defaultx()
{
	EGLNativeDisplayType id = EGLNativeDisplayType(-1);
#if NB_OS == NB_OS_LINUX && NB_ARCH == NB_ARCH_ARM
	id = (EGLNativeDisplayType)(wl_display_connect(nullptr));	//如果使用wayland，传入EGL_DEFAULT_DISPLAY会导致eglInitialize挂死
#else
	id = EGL_DEFAULT_DISPLAY;
#endif
	return Display((long)id);
}
