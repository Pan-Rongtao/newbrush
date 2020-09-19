#include "Window.h"
//#include "parkassist/gles/DrawingContext.h"
//#include "parkassist/gles/Camera.h"

using namespace nb;

#ifndef WIN32

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MAX_DISPLAYS 	(4)
uint8_t DISP_ID = 0;
uint8_t all_display = 0;
int8_t connector_id = -1;

static struct {
	EGLDisplay display;
	EGLConfig config;
	EGLContext context;
	EGLSurface surface;
} gl;

static struct {
	struct gbm_device *dev;
	struct gbm_surface *surface;
} gbm;

static struct {
	int fd;
	uint32_t ndisp;
	uint32_t crtc_id[MAX_DISPLAYS];
	uint32_t connector_id[MAX_DISPLAYS];
	uint32_t resource_id;
	uint32_t encoder[MAX_DISPLAYS];
	drmModeModeInfo *mode[MAX_DISPLAYS];
	drmModeConnector *connectors[MAX_DISPLAYS];
} drm;

struct drm_fb 
{
	struct gbm_bo *bo;
	uint32_t fb_id;
};

struct gbm_bo *m_bo;
fd_set m_fds;

void drm_fb_destroy_callback(struct gbm_bo *bo, void *data)
{
	struct drm_fb *fb = (drm_fb *)data;
	struct gbm_device *gbm = gbm_bo_get_device(bo);

	if (fb->fb_id)
		drmModeRmFB(drm.fd, fb->fb_id);

	free(fb);
}

struct drm_fb * drm_fb_get_from_bo(struct gbm_bo *bo)
{
	struct drm_fb *fb = (drm_fb*)gbm_bo_get_user_data(bo);
	uint32_t width, height, stride, handle;
	int ret;

	if (fb)
		return fb;

	fb = (drm_fb*)calloc(1, sizeof *fb);
	fb->bo = bo;

	width = gbm_bo_get_width(bo);
	height = gbm_bo_get_height(bo);
	stride = gbm_bo_get_stride(bo);
	handle = gbm_bo_get_handle(bo).u32;

	ret = drmModeAddFB(drm.fd, width, height, 24, 32, stride, handle, &fb->fb_id);
	if (ret) {
		printf("failed to create fb: %s\n", strerror(errno));
		free(fb);
		return NULL;
	}

	gbm_bo_set_user_data(bo, fb, drm_fb_destroy_callback);

	return fb;
}

#endif

Window::Window(int width, int height, const std::string &title)
{
	init();

#ifdef WIN32
	m_implWindow = glfwCreateWindow(width, height, title.data(), 0, 0);
	glfwMakeContextCurrent(m_implWindow);
	glfwSetWindowUserPointer(m_implWindow, this);
	glfwSetWindowSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetKeyCallback(m_implWindow, [](GLFWwindow*w, int key, int scancode, int action, int mods) { static_cast<Window *>(glfwGetWindowUserPointer(w))->keyCallback(key, scancode, action, mods);});
	glfwSetCursorPosCallback(m_implWindow, [](GLFWwindow*w, double xpos, double ypos) { static_cast<Window *>(glfwGetWindowUserPointer(w))->cursorPosCallback(xpos, ypos); });
	glfwSetScrollCallback(m_implWindow, [](GLFWwindow*w, double xoffset, double yoffset) { static_cast<Window *>(glfwGetWindowUserPointer(w))->scrollCallback(xoffset, yoffset); });
	sizeCallback(width, height);
#endif
}
 
Window::~Window()
{
}

void Window::swapBuffers()
{
#ifdef WIN32
	glfwSwapBuffers(m_implWindow);
	glfwPollEvents();
#else	
	eglSwapBuffers(gl.display, gl.surface);

	struct gbm_bo *next_bo = gbm_surface_lock_front_buffer(gbm.surface);
	struct drm_fb *fb = drm_fb_get_from_bo(next_bo);
	int waiting_for_flip = 1;
	int ret = drmModePageFlip(drm.fd, drm.crtc_id[DISP_ID], fb->fb_id, DRM_MODE_PAGE_FLIP_EVENT, &waiting_for_flip);
	if (ret)
	{
		printf("failed to queue page flip: %s\n", strerror(errno));
		return;
	}

	while (waiting_for_flip) 
	{
		ret = select(drm.fd + 1, &m_fds, NULL, NULL, NULL);
		if (ret < 0)				{ printf("select err: %s\n", strerror(errno)); return; }
		else if (ret == 0)			{ printf("select timeout!\n"); return; }
		else if (FD_ISSET(0, &m_fds)) { continue; }

		static drmEventContext evctx = { .version = DRM_EVENT_CONTEXT_VERSION,
			.vblank_handler = [](int fd, unsigned int frame, unsigned int sec, unsigned int usec, void *data) {},
			.page_flip_handler = [](int fd, unsigned int frame, unsigned int sec, unsigned int usec, void *data)
			{
				int *waiting_for_flip = (int*)data;
				*waiting_for_flip = 0;
			},
		};
		drmHandleEvent(drm.fd, &evctx);
	}

	/* release last buffer to render on again: */
	gbm_surface_release_buffer(gbm.surface, m_bo);
	m_bo = next_bo;
#endif
}

void Window::resize(int width, int height)
{
#ifdef WIN32
	glfwSetWindowSize(m_implWindow, width, height);
#endif
}

int Window::width() const
{
	int w = 0, h = 0;
#ifdef WIN32
	glfwGetWindowSize(m_implWindow, &w, &h);
#endif
	return w;
}

int Window::height() const
{
	int w = 0, h = 0;
#ifdef WIN32
	glfwGetWindowSize(m_implWindow, &w, &h);
#endif
	return h;
}

void Window::init()
{
	static bool bInit = false;
	if (bInit)	return;

#ifdef WIN32
	glfwSetErrorCallback([](int error, const char*str) { printf("error:%s\n", str); });
	glfwInit();
	//以下两句在有些电脑上导致glfwDestroyWindow挂死，放在库外不会挂死，目前暂未找到原因
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 32);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
	auto ret = initDRM();
	if (ret != 0) { printf("failed to initialize DRM\n"); return; }
	printf("### Primary display => ConnectorId = %d, Resolution = %dx%d\n", drm.connector_id[DISP_ID], drm.mode[DISP_ID]->hdisplay, drm.mode[DISP_ID]->vdisplay);

	ret = initGBM();
	if (ret) { printf("failed to initialize GBM\n"); return; }

	ret = initEGL();
	if (ret) { printf("failed to initialize EGL\n"); return; }


	FD_ZERO(&m_fds);
	FD_SET(drm.fd, &m_fds);
	eglSwapBuffers(gl.display, gl.surface);
	m_bo = gbm_surface_lock_front_buffer(gbm.surface);
	struct drm_fb *fb = drm_fb_get_from_bo(m_bo);

	/* set mode: */
	int all_display = 0;
	if (all_display) 
	{
		for (int i = 0; i<drm.ndisp; i++) 
		{
			ret = drmModeSetCrtc(drm.fd, drm.crtc_id[i], fb->fb_id, 0, 0, &drm.connector_id[i], 1, drm.mode[i]);
			if (ret) 
			{
				printf("display %d failed to set mode: %s\n", i, strerror(errno));
				return;
			}
		}
	}
	else 
	{
		ret = drmModeSetCrtc(drm.fd, drm.crtc_id[DISP_ID], fb->fb_id, 0, 0, &drm.connector_id[DISP_ID], 1, drm.mode[DISP_ID]);
		if (ret) 
		{
			printf("display %d failed to set mode: %s\n", DISP_ID, strerror(errno));
			return;
		}
	}
#endif

	bInit = true;
}

void Window::sizeCallback(int width, int height)
{
	ResizeEvent.invoke(Size{ width, height });
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
	if (action == 1 || action == 2)
	{
		KeyEvent.invoke({ key });
		if (key == GLFW_KEY_ESCAPE)
		{
			exit(0);
		}
	}
}

void Window::cursorPosCallback(double xpos, double ypos)
{
	CursorPosEvent.invoke({(float)xpos, (float)ypos});
}

void Window::scrollCallback(double xoffset, double yoffset)
{
	ScrollEvent.invoke({ (float)xoffset, (float)yoffset });
}

#ifndef WIN32

int Window::initEGL()
{
	EGLint major, minor, n;

	static const EGLint context_attribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	int samples = 4;
	static const EGLint config_attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_ALPHA_SIZE, 0,
		EGL_SAMPLES, samples,
		EGL_NONE
	};
	printf("EGL_SAMPLES=%d\n", samples);

	gl.display = eglGetDisplay((EGLNativeDisplayType)gbm.dev);

	if (!eglInitialize(gl.display, &major, &minor))
	{
		printf("failed to initialize\n");
		return -1;
	}

	printf("Using display %p with EGL version %d.%d\n",
		gl.display, major, minor);

	printf("EGL Version \"%s\"\n", eglQueryString(gl.display, EGL_VERSION));
	printf("EGL Vendor \"%s\"\n", eglQueryString(gl.display, EGL_VENDOR));
	printf("EGL Extensions \"%s\"\n", eglQueryString(gl.display, EGL_EXTENSIONS));

	if (!eglBindAPI(EGL_OPENGL_ES_API)) {
		printf("failed to bind api EGL_OPENGL_ES_API\n");
		return -1;
	}

	if (!eglChooseConfig(gl.display, config_attribs, &gl.config, 1, &n) || n != 1) {
		printf("failed to choose config: %d\n", n);
		return -1;
	}

	gl.context = eglCreateContext(gl.display, gl.config,
		EGL_NO_CONTEXT, context_attribs);
	if (gl.context == NULL) {
		printf("failed to create context\n");
		return -1;
	}

	gl.surface = eglCreateWindowSurface(gl.display, gl.config, gbm.surface, NULL);
	if (gl.surface == EGL_NO_SURFACE) {
		printf("failed to create egl surface\n");
		return -1;
	}

	/* connect the context to the surface */
	eglMakeCurrent(gl.display, gl.surface, gl.surface, gl.context);

	return 0;
}

int Window::initDRM()
{
	static const char *modules[] = {
		"omapdrm", "i915", "radeon", "nouveau", "vmwgfx", "exynos"
	};
	drmModeRes *resources;
	drmModeConnector *connector = NULL;
	drmModeEncoder *encoder = NULL;
	int i, j;
	uint32_t maxRes, curRes;

	for (i = 0; i < ARRAY_SIZE(modules); i++) {
		printf("trying to load module %s...", modules[i]);
		drm.fd = drmOpen(modules[i], NULL);
		if (drm.fd < 0) {
			printf("failed.\n");
		}
		else {
			printf("success.\n");
			break;
		}
	}

	if (drm.fd < 0) {
		printf("could not open drm device\n");
		return -1;
	}

	resources = drmModeGetResources(drm.fd);
	if (!resources) {
		printf("drmModeGetResources failed: %s\n", strerror(errno));
		return -1;
	}
	drm.resource_id = (uint32_t)resources;

	/* find a connected connector: */
	for (i = 0; i < resources->count_connectors; i++) {
		connector = drmModeGetConnector(drm.fd, resources->connectors[i]);
		if (connector->connection == DRM_MODE_CONNECTED) {
			/* choose the first supported mode */
			drm.mode[drm.ndisp] = &connector->modes[0];
			drm.connector_id[drm.ndisp] = connector->connector_id;

			for (j = 0; j<resources->count_encoders; j++) {
				encoder = drmModeGetEncoder(drm.fd, resources->encoders[j]);
				if (encoder->encoder_id == connector->encoder_id)
					break;

				drmModeFreeEncoder(encoder);
				encoder = NULL;
			}

			if (!encoder) {
				printf("no encoder!\n");
				return -1;
			}

			drm.encoder[drm.ndisp] = (uint32_t)encoder;
			drm.crtc_id[drm.ndisp] = encoder->crtc_id;
			drm.connectors[drm.ndisp] = connector;

			printf("### Display [%d]: CRTC = %d, Connector = %d\n", drm.ndisp, drm.crtc_id[drm.ndisp], drm.connector_id[drm.ndisp]);
			printf("\tMode chosen [%s] : Clock => %d, Vertical refresh => %d, Type => %d\n", drm.mode[drm.ndisp]->name, drm.mode[drm.ndisp]->clock, drm.mode[drm.ndisp]->vrefresh, drm.mode[drm.ndisp]->type);
			printf("\tHorizontal => %d, %d, %d, %d, %d\n", drm.mode[drm.ndisp]->hdisplay, drm.mode[drm.ndisp]->hsync_start, drm.mode[drm.ndisp]->hsync_end, drm.mode[drm.ndisp]->htotal, drm.mode[drm.ndisp]->hskew);
			printf("\tVertical => %d, %d, %d, %d, %d\n", drm.mode[drm.ndisp]->vdisplay, drm.mode[drm.ndisp]->vsync_start, drm.mode[drm.ndisp]->vsync_end, drm.mode[drm.ndisp]->vtotal, drm.mode[drm.ndisp]->vscan);

			/* If a connector_id is specified, use the corresponding display */
			if ((connector_id != -1) && (connector_id == drm.connector_id[drm.ndisp]))
				DISP_ID = drm.ndisp;

			/* If all displays are enabled, choose the connector with maximum
			* resolution as the primary display */
			if (all_display) {
				maxRes = drm.mode[DISP_ID]->vdisplay * drm.mode[DISP_ID]->hdisplay;
				curRes = drm.mode[drm.ndisp]->vdisplay * drm.mode[drm.ndisp]->hdisplay;

				if (curRes > maxRes)
					DISP_ID = drm.ndisp;
			}

			drm.ndisp++;
		}
		else {
			drmModeFreeConnector(connector);
		}
	}

	if (drm.ndisp == 0) {
		/* we could be fancy and listen for hotplug events and wait for
		* a connector..
		*/
		printf("no connected connector!\n");
		return -1;
	}

	return 0;
}

int Window::initGBM()
{
	gbm.dev = gbm_create_device(drm.fd);

	gbm.surface = gbm_surface_create(gbm.dev,
		drm.mode[DISP_ID]->hdisplay, drm.mode[DISP_ID]->vdisplay,
		GBM_FORMAT_XRGB8888,
		GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
	if (!gbm.surface) {
		printf("failed to create gbm surface\n");
		return -1;
	}

	return 0;
}

void Window::deinitDRM()
{
	drmModeRes *resources;
	int i;

	resources = (drmModeRes *)drm.resource_id;
	for (i = 0; i < resources->count_connectors; i++) {
		drmModeFreeEncoder((drmModeEncoderPtr)drm.encoder[i]);
		drmModeFreeConnector(drm.connectors[i]);
	}
	drmModeFreeResources((drmModeResPtr)drm.resource_id);
	drmClose(drm.fd);
	return;
}

void Window::deinitGBM()
{
	gbm_surface_destroy(gbm.surface);
	gbm_device_destroy(gbm.dev);
	return;
}

void Window::deinitEGL()
{
	eglDestroySurface(gl.display, gl.surface);
	eglDestroyContext(gl.display, gl.context);
	eglTerminate(gl.display);
}


#endif // Win32
