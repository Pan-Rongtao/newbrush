#pragma once
#include <string>
#include "newbrush/model/Event.h"
#ifdef WIN32
#include "GLFW/glfw3.h"
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "xf86drm.h"
#include "xf86drmMode.h"
#include "gbm/gbm.h"
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#endif

struct GLFWwindow;
namespace nb {

struct Size { int width; int height; };
struct Point { float x; float y; };

class Window
{
public:
	Window(int width = 800, int height = 600, const std::string &title = "newbrush");
	~Window();

	void swapBuffers();

	void resize(int width, int height);

	int width() const;
	int height() const;

	Event<int>	KeyEvent;
	Event<Size>	ResizeEvent;
	Event<Point> CursorPosEvent;
	Event<Point> ScrollEvent;

private:
	static void init();

	void sizeCallback(int width, int height);
	void keyCallback(int key, int scancode, int action, int mods);
	void cursorPosCallback(double xpos, double ypos);
	void scrollCallback(double xoffset, double yoffset);

#ifdef WIN32
	GLFWwindow *m_implWindow;
#else

	static int initEGL();
	static int initDRM();
	static int initGBM();
	void deinitEGL();
	void deinitDRM();
	void deinitGBM();

#endif // WIN23

};

using WindowPtr = std::shared_ptr<Window>;

}
