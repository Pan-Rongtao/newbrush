#include "gles/Application.h"
#include <GLES2/gl2.h>
#include "gles/Egl.h"
#include "gles/Window.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/RenderObject.h"
#include "EglMaster.h"
#include "core/Log.h"

using namespace nb;
using namespace nb::gl;

Application::Application(std::shared_ptr<Display> display, std::shared_ptr<Configure> configure)
{
	static bool instanced = false;
	if (instanced)
		nbThrowException(std::runtime_error, "create more than one application object");

	//初始化GL，注意，使用Configure((int *)nullptr)开启深度帧率降低很多
	if(!display)	display = std::make_shared<Display>(Display::defaultx());
	nb::gl::initialize(display);
	if(!configure)	configure = std::make_shared<Configure>(Configure::fromSystemRecommend(0))/*Configure((int *)nullptr)*/;
	nb::gl::setConfigure(configure);
	instanced = true;
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
			gl::swapBuffers(ws);
	}
}

void Application::render()
{
	static int frames = 0;
	static uint64_t k = nb::getTickCount();
	for (auto const &context : EglMaster::contexts())
		context->draw();

	++frames;
	uint64_t kk = nb::getTickCount();
	if(kk - k >= 2000)
	{
		float fps = frames * 1000.0f / (kk - k);
		frames = 0;
		k = kk;
		Log::info("fps:%.2f", fps);
	}
}
