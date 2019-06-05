#include "gles/Application.h"
#include <GLES2/gl2.h>
#include "gles/Egl.h"
#include "gles/Window.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/RenderObject.h"
#include "EglMaster.h"

using namespace nb::core;
using namespace nb::gl;

static bool g_hasInstanced = false;
Application::Application(std::shared_ptr<Display> display, std::shared_ptr<Configure> configure)
{
	if (g_hasInstanced)
		NB_THROW_EXCEPTION(std::runtime_error, "create more than one application object");

	//初始化GL，注意，使用Configure((int *)NULL)开启深度帧率降低很多
	if(!display)
		display = std::make_shared<Display>(Display::defaultx());
	nb::gl::initialize(display);
	if(!configure)
		configure = std::make_shared<Configure>(Configure::fromSystemRecommend(0))/*Configure((int *)nullptr)*/;
	nb::gl::setConfigure(configure);
	g_hasInstanced = true;
}

int Application::run()
{
	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		preRender();
		render();
		postRender();

		for (auto const &w : EglMaster::windows())
			w->pending();

		for(auto const &ws : EglMaster::windowSurfaces())
			nb::gl::swapBuffers(ws);
	}
}

void Application::render()
{
	static int frames = 0;
	static uint64_t k = NB_TICK_COUT;
	for (auto const &context : EglMaster::contexts())
		context->draw();

	++frames;
	uint64_t kk = NB_TICK_COUT;
	if(kk - k >= 2000)
	{
		float fps = frames * 1000.0f / (kk - k);
		frames = 0;
		k = kk;
		printf("fps:%.2f\r\n", fps);
	}
}
